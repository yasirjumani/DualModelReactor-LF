#if defined(PLATFORM_RP2040)
/**
 * @file
 * @brief RP2040 mcu support for the C target of Lingua Franca.
 *
 * This utilizes the pico-sdk which provides C methods for a light runtime
 * and a hardware abstraction layer.
 *
 * @author Abhi Gundrala
 */

#include "platform/lf_rp2040_support.h"
#include "low_level_platform.h"
#include "tag.h"

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/sync.h>

/**
 * critical section struct
 * disables external irq and core execution
 * provides mutual exclusion using hardware spin-locks
 */
static critical_section_t _lf_crit_sec;

/**
 * binary semaphore for lf event notification
 * used by external isr or second core thread.
 * used to interact with the lf runtime thread
 */
static semaphore_t _lf_sem_irq_event;

// nested critical section counter
static uint32_t _lf_num_nested_crit_sec = 0;

/**
 * Initialize basic runtime infrastructure and
 * synchronization structs for an single-threaded runtime.
 */
void _lf_initialize_clock(void) {
  // init stdio lib
  // may fail, but failure may be ok/expected if printing is not needed
  // (i.e. if neither USB nor UART are enabled)
  stdio_init_all();
  // init sync structs
  critical_section_init(&_lf_crit_sec);
  sem_init(&_lf_sem_irq_event, 0, 1);
}

/**
 * Write the time since boot in nanoseconds into
 * the time variable pointed to by the argument
 * and return 0.
 *
 * @param  t  pointer to the time variable to write to.
 * @return error code or 0 on success.
 */
int _lf_clock_gettime(instant_t* t) {
  if (!t) {
    return -1;
  }
  // time struct
  absolute_time_t now;
  uint64_t ns_from_boot;

  now = get_absolute_time();
  ns_from_boot = to_us_since_boot(now) * 1000;
  *t = (instant_t)ns_from_boot;
  return 0;
}

/**
 * Pause execution of the calling core for
 * a nanosecond duration specified by the argument.
 * Floor the specified duration to the nearest microsecond
 * duration before sleeping and return 0.
 *
 * @param  sleep_duration  time to sleep in nanoseconds
 * @return error code or 0 on success
 */
int lf_sleep(interval_t sleep_duration) {
  if (sleep_duration < 0) {
    return -1;
  }
  sleep_us((uint64_t)(sleep_duration / 1000));
  return 0;
}

/**
 * Sleep until the target time since boot in nanoseconds provided
 * by the argument or return early if the binary
 * _lf_sem_irq_event semaphore is released before the target time.
 *
 * The semaphore is released using the _lf_single_threaded_notify_of_event
 * which is called by lf_schedule in the single_threaded runtime for physical actions.
 *
 * @param  env  pointer to environment struct this runs in.
 * @param  wakeup_time  time in nanoseconds since boot to sleep until.
 * @return -1 when interrupted or 0 on successful timeout
 */
int _lf_interruptable_sleep_until_locked(environment_t* env, instant_t wakeup_time) {
  int ret_code = 0;
  // return immediately
  if (wakeup_time < 0) {
    return ret_code;
  }
  // time struct
  absolute_time_t target;

  // reset event semaphore
  sem_reset(&_lf_sem_irq_event, 0);
  // create us boot wakeup time
  target = from_us_since_boot((uint64_t)(wakeup_time / 1000));
  // Enable interrupts.
  lf_critical_section_exit(env);
  // blocked sleep
  // return on timeout or on processor event
  if (sem_acquire_block_until(&_lf_sem_irq_event, target)) {
    ret_code = -1;
  }
  // Disable interrupts.
  lf_critical_section_enter(env);
  return ret_code;
}

/**
 * Enter a critical section where the second core is disabled
 * and interrupts are disabled. Enter only if the critical section
 * hasn't previously been entered.
 *
 * @return error code or 0 on success
 */
int lf_disable_interrupts_nested() {
  if (!critical_section_is_initialized(&_lf_crit_sec)) {
    return 1;
  }
  // check crit sec count
  // enter non-reentrant state by disabling interrupts
  // lock second core execution
  if (_lf_num_nested_crit_sec == 0) {
    // block if associated spin lock in use
    critical_section_enter_blocking(&_lf_crit_sec);
  }
  // add crit sec count
  _lf_num_nested_crit_sec++;
  return 0;
}

/**
 * Exit a critical section which will resume second core
 * execution and enable interrupts.
 * Exit only if no other critical sections are left to exit.
 *
 * @return error code or 0 on success
 */
int lf_enable_interrupts_nested() {
  if (!critical_section_is_initialized(&_lf_crit_sec) || _lf_num_nested_crit_sec <= 0) {
    return 1;
  }
  // remove from crit sec count
  _lf_num_nested_crit_sec--;
  // check crit sec count
  // release spin-lock
  if (_lf_num_nested_crit_sec == 0) {
    critical_section_exit(&_lf_crit_sec);
  }
  return 0;
}

#if defined(LF_SINGLE_THREADED)
/**
 * Release the binary event semaphore to notify
 * the runtime of a physical action being scheduled.
 *
 * @return error code or 0 on success
 */
int _lf_single_threaded_notify_of_event() {
  // notify main sleep loop of event
  if (sem_release(&_lf_sem_irq_event)) {
    return 0;
  }
  return 1;
}

#else // LF_SINGLE_THREADED

#warning "Threaded runtime on RP2040 is still experimental"

/**
 * @brief Get the number of cores on the host machine.
 */
int lf_available_cores() { return 2; }

static void* (*thread_1)(void*);
static void* thread_1_args;
static int num_create_threads_called = 0;
static semaphore_t thread_1_done;
static void* thread_1_return;

#define MAGIC_THREAD1_ID 314159

void core1_entry() {
  thread_1_return = thread_1(thread_1_args);
  sem_reset(&thread_1_done, 1);
}

int lf_thread_create(lf_thread_t* thread, void* (*lf_thread)(void*), void* arguments) {
  // make sure this fn is only called once
  if (num_create_threads_called != 0) {
    return 1;
  }
  thread_1 = lf_thread;
  thread_1_args = arguments;
  num_create_threads_called += 1;
  sem_init(&thread_1_done, 0, 1);
  multicore_launch_core1(core1_entry);
  *thread = MAGIC_THREAD1_ID;
  return 0;
}

int lf_thread_join(lf_thread_t thread, void** thread_return) {
  if (thread != MAGIC_THREAD1_ID) {
    return 1;
  }
  sem_acquire_blocking(&thread_1_done);
  // release in case join is called again
  if (!sem_release(&thread_1_done)) {
    // shouldn't be possible; lf_thread_join is only called from main thread
    return 1;
  }
  if (thread_return) {
    *thread_return = thread_1_return;
  }
  return 0;
}

int lf_mutex_init(lf_mutex_t* mutex) {
  recursive_mutex_init(mutex);
  return 0;
}

int lf_mutex_lock(lf_mutex_t* mutex) {
  recursive_mutex_enter_blocking(mutex);
  return 0;
}

int lf_mutex_unlock(lf_mutex_t* mutex) {
  recursive_mutex_exit(mutex);
  return 0;
}

// condition variables "notify" threads using a semaphore per core.
// although there are only two cores, may not use just a single semaphore
// as a cond_broadcast may be called from within an interrupt
int lf_cond_init(lf_cond_t* cond, lf_mutex_t* mutex) {
  for (int i = 0; i < NUM_CORES; i++) {
    sem_init(&(cond->notifs[i]), 0, 1);
  }
  cond->mutex = mutex;
  return 0;
}

int lf_cond_broadcast(lf_cond_t* cond) {
  for (int i = 0; i < NUM_CORES; i++) {
    sem_reset(&(cond->notifs[i]), 1);
  }
  return 0;
}

int lf_cond_signal(lf_cond_t* cond) {
  return lf_cond_broadcast(cond); // spurious wakeups, but that's ok
}

int lf_cond_wait(lf_cond_t* cond) {
  semaphore_t* mailbox = &(cond->notifs[get_core_num()]);
  lf_mutex_unlock(cond->mutex);
  sem_acquire_blocking(mailbox);
  lf_mutex_lock(cond->mutex);
  return 0;
}

int _lf_cond_timedwait(lf_cond_t* cond, instant_t absolute_time_ns) {
  semaphore_t* mailbox = &(cond->notifs[get_core_num()]);
  absolute_time_t a = from_us_since_boot(absolute_time_ns / 1000);
  bool acquired_permit = sem_acquire_block_until(mailbox, a);
  return acquired_permit ? 0 : LF_TIMEOUT;
}

void initialize_lf_thread_id() {}

int lf_thread_id() { return get_core_num(); }

#endif // !LF_SINGLE_THREADED

#endif // PLATFORM_RP2040
