/**
 * @file
 * @author Benjamin Asch
 * @author Edward A. Lee
 * @author Erling Jellum
 *
 * @brief Definitions for watchdogs.
 */

#include <assert.h>
#include "watchdog.h"
#include "environment.h"
#include "util.h"
#include "clock.h"

// Forward declarations
static void _lf_watchdog_terminate(watchdog_t* watchdog);
static void* watchdog_thread_main(void* arg);

/**
 * @brief Initialize watchdog mutexes.
 * For any reactor with one or more watchdogs, the self struct should have a non-NULL
 * `reactor_mutex` field which points to an instance of `lf_mutex_t`.
 * This function initializes those mutexes. It also initializes the condition
 * variable which enables the safe termination of a running watchdog.
 * Finally it starts of a non-termminating thread for each watchdog.
 */
void _lf_initialize_watchdogs(environment_t* env) {
  for (int i = 0; i < env->watchdogs_size; i++) {
    watchdog_t* watchdog = env->watchdogs[i];
    if (watchdog->base->reactor_mutex != NULL) {
      LF_MUTEX_INIT((lf_mutex_t*)(watchdog->base->reactor_mutex));
    }
    LF_COND_INIT(&watchdog->cond, watchdog->base->reactor_mutex);

    int ret = lf_thread_create(&watchdog->thread_id, watchdog_thread_main, (void*)watchdog);
    LF_ASSERTN(ret, "Could not create watchdog thread");
  }
}

/**
 * @brief Terminate all watchdog threads.
 */
void _lf_watchdog_terminate_all(environment_t* env) {
  void* thread_ret;
  for (int i = 0; i < env->watchdogs_size; i++) {
    watchdog_t* watchdog = env->watchdogs[i];
    LF_MUTEX_LOCK(watchdog->base->reactor_mutex);
    _lf_watchdog_terminate(watchdog);
    LF_MUTEX_UNLOCK(watchdog->base->reactor_mutex);
    lf_thread_join(watchdog->thread_id, &thread_ret);
  }
}

void watchdog_wait(watchdog_t* watchdog) {
  watchdog->active = true;
  instant_t physical_time = lf_time_physical();
  while (watchdog->expiration != NEVER && physical_time < watchdog->expiration && !watchdog->terminate) {
    // Wait for expiration, or a signal to stop or terminate.
    LF_PRINT_DEBUG("Watchdog %p sleeps until " PRINTF_TIME, (void*)watchdog, watchdog->expiration);
    lf_clock_cond_timedwait(&watchdog->cond, watchdog->expiration);
    physical_time = lf_time_physical();
    LF_PRINT_DEBUG("Watchdog %p woke up at " PRINTF_TIME " expires at " PRINTF_TIME, (void*)watchdog, physical_time,
                   watchdog->expiration);
  }
  LF_PRINT_DEBUG("Watchdog %p returns with expired=%d terminated=%d", (void*)watchdog,
                 physical_time >= watchdog->expiration, watchdog->terminate);
}

/**
 * @brief Thread function for a watchdog.
 *
 * Each watchdog has a thread which sleeps until one out of two scenarios:
 * 1) The watchdog timeout expires and there has not been a renewal of the
 *    watchdog budget.
 * 2) The watchdog is signaled to wake up and stop or terminate.
 *
 * In normal usage, the expiration time is incremented while the thread is
 * sleeping, so when the thread wakes up, it can go back to sleep again. If the
 * watchdog does expire. It will execute the watchdog handler and wait for next
 * start. To stop a running watchdog, the expiration field is set to NEVER.
 * The watchdog thread can also be terminated, this should only be done at the
 * end of execution as it cannot be restarted after termination.
 *
 * @param arg A pointer to the watchdog struct
 * @return NULL
 */
static void* watchdog_thread_main(void* arg) {
  initialize_lf_thread_id();
  watchdog_t* watchdog = (watchdog_t*)arg;
  self_base_t* base = watchdog->base;
  LF_PRINT_DEBUG("Starting Watchdog %p", (void*)watchdog);
  LF_ASSERT(base->reactor_mutex, "reactor-mutex not alloc'ed but has watchdogs.");

  // Grab reactor-mutex and start infinite loop.
  LF_MUTEX_LOCK((lf_mutex_t*)(base->reactor_mutex));
  while (!watchdog->terminate) {

    // Step 1: Wait for a timeout to start watching for.
    if (watchdog->expiration == NEVER) {
      LF_PRINT_DEBUG("Watchdog %p waiting on cond var to be started", (void*)watchdog);
      // Watchdog has been stopped.
      // Let the runtime know that we are in an inactive/stopped state.
      watchdog->active = false;
      // Wait here until the watchdog is started and we can enter the active state.
      LF_COND_WAIT(&watchdog->cond);
      LF_PRINT_DEBUG("Watchdog %p woke up from cond var", (void*)watchdog);
      continue;
    } else {
      // Watchdog has been started.
      LF_PRINT_DEBUG("Watchdog %p started", (void*)watchdog);
      watchdog_wait(watchdog);

      // At this point we have returned from the watchdog wait. But it could
      // be that it was to terminate the watchdog.
      if (watchdog->terminate) {
        LF_PRINT_DEBUG("Watchdog %p was terminated", (void*)watchdog);
        break;
      }

      // It could also be that the watchdog was stopped
      if (watchdog->expiration == NEVER) {
        LF_PRINT_DEBUG("Watchdog %p was stopped", (void*)watchdog);
        continue;
      }

      // If we reach here, the watchdog actually timed out. Handle it.
      LF_PRINT_DEBUG("Watchdog %p timed out", (void*)watchdog);
      watchdog_function_t watchdog_func = watchdog->watchdog_function;
      (*watchdog_func)(base);
      watchdog->expiration = NEVER;
    }
  }

  // Here the thread terminates.
  watchdog->active = false;
  LF_MUTEX_UNLOCK(base->reactor_mutex);
  return NULL;
}

void lf_watchdog_start(watchdog_t* watchdog, interval_t additional_timeout) {
  // Assumes reactor mutex is already held.
  self_base_t* base = watchdog->base;
  watchdog->terminate = false;
  watchdog->expiration = base->environment->current_tag.time + watchdog->min_expiration + additional_timeout;

  // If the watchdog is inactive, signal it to start waiting.
  if (!watchdog->active) {
    LF_COND_SIGNAL(&watchdog->cond);
  }
}

void lf_watchdog_stop(watchdog_t* watchdog) {
  // Assumes reactor mutex is already held.
  watchdog->expiration = NEVER;

  // If lf_watchdog_stop is called very close to lf_watchdog_start, it might
  // not have had the time to wake up and start sleeping.
  if (!watchdog->active) {
    return;
  }

  LF_COND_SIGNAL(&watchdog->cond);
}

static void _lf_watchdog_terminate(watchdog_t* watchdog) {
  watchdog->terminate = true;
  watchdog->expiration = NEVER;
  LF_COND_SIGNAL(&watchdog->cond);
}
