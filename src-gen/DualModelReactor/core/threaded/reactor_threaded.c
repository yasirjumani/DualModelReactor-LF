/**
 * @file
 * @author Edward A. Lee
 * @author Marten Lohstroh
 * @author Soroush Bateni
 *
 * @brief  Runtime infrastructure for the threaded version of the C target of Lingua Franca.
 */
#if !defined LF_SINGLE_THREADED
#ifndef NUMBER_OF_WORKERS
#define NUMBER_OF_WORKERS 1
#endif // NUMBER_OF_WORKERS

#include <assert.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#include "lf_types.h"
#include "low_level_platform.h"
#include "reactor_threaded.h"
#include "reactor.h"
#include "scheduler.h"
#include "tag.h"
#include "environment.h"
#include "rti_local.h"
#include "reactor_common.h"
#include "watchdog.h"

#ifdef FEDERATED
#include "federate.h"
#endif

// Global variables defined in tag.c and shared across environments:
extern instant_t start_time;

/**
 * The maximum amount of time a worker thread should stall
 * before checking the reaction queue again.
 * This is not currently used.
 */
#define MAX_STALL_INTERVAL MSEC(1)

/**
 * Global mutex, used for synchronizing across environments. Mainly used for token-management and tracing
 */
lf_mutex_t global_mutex;

void _lf_increment_tag_barrier_locked(environment_t* env, tag_t future_tag) {
  assert(env != GLOBAL_ENVIRONMENT);

  // Check if future_tag is after stop tag.
  // This will only occur when a federate receives a timed message with
  // a tag that is after the stop tag
  if (lf_is_tag_after_stop_tag(env, future_tag)) {
    lf_print_warning("Attempting to raise a barrier after the stop tag.");
    future_tag = env->stop_tag;
  }

  // Check to see if future_tag is actually in the future.
  if (lf_tag_compare(future_tag, env->current_tag) > 0) {
    // Future tag is actually in the future.
    // See whether it is smaller than any pre-existing barrier.
    if (lf_tag_compare(future_tag, env->barrier.horizon) < 0) {
      // The future tag is smaller than the current horizon of the barrier.
      // Therefore, we should prevent logical time from reaching the
      // future tag.
      env->barrier.horizon = future_tag;
      LF_PRINT_DEBUG("Raised barrier at elapsed tag " PRINTF_TAG ".", env->barrier.horizon.time - start_time,
                     env->barrier.horizon.microstep);
    }
  } else {
    // The future_tag is not in the future.

    // One possibility is that the incoming message has violated the STP offset.
    // Another possibility is that the message is coming from a zero-delay loop,
    // and port absent reactions are waiting.

    // Prevent logical time from advancing further so that the measure of
    // STP violation properly reflects the amount of time (logical or physical)
    // that has elapsed after the incoming message would have violated the STP offset.
    env->barrier.horizon = env->current_tag;
    env->barrier.horizon.microstep++;
    LF_PRINT_DEBUG("Raised barrier at elapsed tag " PRINTF_TAG ".", env->barrier.horizon.time - start_time,
                   env->barrier.horizon.microstep);
  }
  // Increment the number of requestors
  env->barrier.requestors++;
}

void _lf_increment_tag_barrier(environment_t* env, tag_t future_tag) {
  assert(env != GLOBAL_ENVIRONMENT);
  LF_MUTEX_LOCK(&env->mutex);
  _lf_increment_tag_barrier_locked(env, future_tag);
  LF_MUTEX_UNLOCK(&env->mutex);
}

void _lf_decrement_tag_barrier_locked(environment_t* env) {
  assert(env != GLOBAL_ENVIRONMENT);
  // Decrement the number of requestors for the tag barrier.
  env->barrier.requestors--;
  // Check to see if the semaphore is negative, which indicates that
  // a mismatched call was placed for this function.
  if (env->barrier.requestors < 0) {
    lf_print_error_and_exit("Mismatched use of _lf_increment_tag_barrier()"
                            " and  _lf_decrement_tag_barrier_locked().");
  } else if (env->barrier.requestors == 0) {
    // When the semaphore reaches zero, reset the horizon to forever.
    env->barrier.horizon = FOREVER_TAG;
    // Notify waiting threads that the semaphore has reached zero.
    lf_cond_broadcast(&env->global_tag_barrier_requestors_reached_zero);
  }
  LF_PRINT_DEBUG("Barrier is at tag " PRINTF_TAG ".", env->barrier.horizon.time, env->barrier.horizon.microstep);
}

int _lf_wait_on_tag_barrier(environment_t* env, tag_t proposed_tag) {
  assert(env != GLOBAL_ENVIRONMENT);

  // Check the most common case first.
  if (env->barrier.requestors == 0)
    return 0;

  // Do not wait for tags after the stop tag
  if (lf_is_tag_after_stop_tag(env, proposed_tag)) {
    proposed_tag = env->stop_tag;
  }
  // Do not wait forever
  if (proposed_tag.time == FOREVER) {
    lf_print_warning("Global tag barrier should not handle FOREVER proposed tags.");
    return 0;
  }
  int result = 0;
  // Wait until the global barrier semaphore on logical time is zero
  // and the proposed_time is larger than or equal to the horizon.
  while (env->barrier.requestors > 0 && lf_tag_compare(proposed_tag, env->barrier.horizon) >= 0) {
    result = 1;
    LF_PRINT_LOG("Waiting on barrier for tag " PRINTF_TAG ".", proposed_tag.time - start_time, proposed_tag.microstep);
    // Wait until no requestor remains for the barrier on logical time
    lf_cond_wait(&env->global_tag_barrier_requestors_reached_zero);

    // The stop tag may have changed during the wait.
    if (lf_is_tag_after_stop_tag(env, proposed_tag)) {
      proposed_tag = env->stop_tag;
    }
  }
  LF_PRINT_LOG("Finished waiting on barrier for tag " PRINTF_TAG ".", proposed_tag.time - start_time,
               proposed_tag.microstep);
  return result;
}

void lf_set_present(lf_port_base_t* port) {
  if (!port->source_reactor)
    return;
  environment_t* env = port->source_reactor->environment;
  bool* is_present_field = &port->is_present;
  int ipfas = lf_atomic_fetch_add(&env->is_present_fields_abbreviated_size, 1);
  if (ipfas < env->is_present_fields_size) {
    env->is_present_fields_abbreviated[ipfas] = is_present_field;
  }
  *is_present_field = true;

  // Support for sparse destination multiports.
  if (port->sparse_record && port->destination_channel >= 0 && port->sparse_record->size >= 0) {
    size_t next = (size_t)lf_atomic_fetch_add(&port->sparse_record->size, 1);
    if (next >= port->sparse_record->capacity) {
      // Buffer is full. Have to revert to the classic iteration.
      port->sparse_record->size = -1;
    } else {
      port->sparse_record->present_channels[next] = port->destination_channel;
    }
  }
}

bool wait_until(instant_t wait_until_time, lf_cond_t* condition) {
  if (!fast || (wait_until_time == FOREVER && keepalive_specified)) {
    LF_PRINT_DEBUG("-------- Waiting until physical time " PRINTF_TIME, wait_until_time - start_time);
    // Check whether we actually need to wait, or if we have already passed the timepoint.
    interval_t wait_duration = wait_until_time - lf_time_physical();
    if (wait_duration < 0) {
      LF_PRINT_DEBUG("We have already passed " PRINTF_TIME ". Skipping wait.", wait_until_time);
      return true;
    }

    // We do the sleep on the cond var so we can be awakened by the
    // asynchronous scheduling of a physical action. lf_clock_cond_timedwait
    // returns 0 if it is awakened before the timeout. Hence, we want to run
    // it repeatedly until either it returns non-zero or the current
    // physical time matches or exceeds the logical time.
    if (lf_clock_cond_timedwait(condition, wait_until_time) != LF_TIMEOUT) {
      LF_PRINT_DEBUG("-------- wait_until interrupted before timeout.");

      // Wait did not time out, which means that there
      // may have been an asynchronous call to lf_schedule().
      // If there was an asynchronous call to lf_schedule(), it will have put an event on the event queue,
      // and the tag will be set to that value when that event is pulled.
      return false;
    } else {
      // Reached timeout.
      LF_PRINT_DEBUG("-------- Returned from wait, having waited " PRINTF_TIME " ns.", wait_duration);
      return true;
    }
  }
  return true;
}

tag_t get_next_event_tag(environment_t* env) {
  assert(env != GLOBAL_ENVIRONMENT);

  // Peek at the earliest event in the event queue.
  event_t* event = (event_t*)pqueue_tag_peek(env->event_q);
  tag_t next_tag = FOREVER_TAG;
  if (event != NULL) {
    // There is an event in the event queue.
    if (lf_tag_compare(event->base.tag, env->current_tag) < 0) {
      lf_print_error_and_exit("get_next_event_tag(): Earliest event on the event queue (" PRINTF_TAG ") is "
                              "earlier than the current tag (" PRINTF_TAG ").",
                              event->base.tag.time - start_time, event->base.tag.microstep,
                              env->current_tag.time - start_time, env->current_tag.microstep);
    }

    next_tag = event->base.tag;
  }

  // If a timeout tag was given, adjust the next_tag from the
  // event tag to that timeout tag.
  if (lf_is_tag_after_stop_tag(env, next_tag)) {
    next_tag = env->stop_tag;
  }
  LF_PRINT_LOG("Earliest event on the event queue (or stop time if empty) is " PRINTF_TAG ". Event queue has size %zu.",
               next_tag.time - start_time, next_tag.microstep, pqueue_tag_size(env->event_q));
  return next_tag;
}

tag_t send_next_event_tag(environment_t* env, tag_t tag, bool wait_for_reply) {
#if defined(FEDERATED_CENTRALIZED)
  return lf_send_next_event_tag(env, tag, wait_for_reply);
#elif defined(LF_ENCLAVES)
  return rti_next_event_tag_locked(env->enclave_info, tag);
#else
  (void)env;
  (void)wait_for_reply;
  return tag;
#endif
}

void _lf_next_locked(environment_t* env) {
  assert(env != GLOBAL_ENVIRONMENT);

#ifdef MODAL_REACTORS
  // Perform mode transitions
  _lf_handle_mode_changes(env);
#endif

  // Get the tag of the next event on the event queue.
  tag_t next_tag = get_next_event_tag(env);

#if defined LF_ENCLAVES
  // Request permission to advance time. This call might block.
  tag_t grant_tag = rti_next_event_tag_locked(env->enclave_info, next_tag);

  // If we received are granted a tag which is less than the requested tag
  // then we return and re-do the next function. We might have gotten a new
  // event on the event queue.
  if (lf_tag_compare(grant_tag, next_tag) < 0)
    return;

  // Next event might have changed while waiting for the TAG
  next_tag = get_next_event_tag(env);

  // Check for starvation. If our next tag is FOREVER_TAG now. This means that
  // we have no events on our event queue and that the RTI has granted us a TAG
  // to advance to FOREVER. I.e. all upstream enclaves have terminated and sent
  // an LTC for FOREVER. We can, in this case, terminate the current enclave.
  if (!keepalive_specified && lf_tag_compare(next_tag, FOREVER_TAG) == 0) {
    lf_set_stop_tag(env, (tag_t){.time = env->current_tag.time, .microstep = env->current_tag.microstep + 1});
    next_tag = get_next_event_tag(env);
  }
#elif defined FEDERATED_CENTRALIZED
  // In case this is in a federation with centralized coordination, notify
  // the RTI of the next earliest tag at which this federate might produce
  // an event. This function may block until it is safe to advance the current
  // tag to the next tag. Specifically, it blocks if there are upstream
  // federates. If an action triggers during that wait, it will unblock
  // and return with a time (typically) less than the next_time.
  tag_t grant_tag = send_next_event_tag(env, next_tag, true); // true means this blocks.
  while (lf_tag_compare(grant_tag, next_tag) < 0) {
    next_tag = get_next_event_tag(env);
    grant_tag = send_next_event_tag(env, next_tag, true);
  }
  // Granted tag is greater than or equal to next event tag that we sent to the RTI.
  // Since send_next_event_tag releases the mutex lock internally, we need to check
  // again for what the next tag is (e.g., the stop time could have changed).
  next_tag = get_next_event_tag(env);

  // FIXME: Do starvation analysis for centralized coordination.
  // Specifically, if the event queue is empty on *all* federates, this
  // can become known to the RTI which can then stop execution.
  // Hence, it will no longer be necessary to force keepalive to be true
  // for all federated execution. With centralized coordination, we could
  // allow keepalive to be either true or false and could get the same
  // behavior with centralized coordination as with unfederated execution.

#else // not FEDERATED_CENTRALIZED nor LF_ENCLAVES
  if (pqueue_tag_peek(env->event_q) == NULL && !keepalive_specified) {
    // There is no event on the event queue and keepalive is false.
    // No event in the queue
    // keepalive is not set so we should stop.
    // Note that federated programs with decentralized coordination always have
    // keepalive = true
    lf_set_stop_tag(env, (tag_t){.time = env->current_tag.time, .microstep = env->current_tag.microstep + 1});

    // Stop tag has changed. Need to check next_tag again.
    next_tag = get_next_event_tag(env);
  }
#endif

  // Wait for physical time to advance to the next event time (or stop time).
  // This can be interrupted if a physical action triggers (e.g., a message
  // arrives from an upstream federate or a local physical action triggers).
  while (true) {
    interval_t wait_until_time = next_tag.time;
#ifdef FEDERATED_DECENTRALIZED
    // Apply the STA, if needed.
    wait_until_time = lf_wait_until_time(next_tag);
#endif // FEDERATED_DECENTRALIZED
    LF_PRINT_LOG("Waiting until elapsed time " PRINTF_TIME ".", (wait_until_time - start_time));
    if (wait_until(wait_until_time, &env->event_q_changed)) {
      // Waited the full time.
      break;
    }
    LF_PRINT_DEBUG("_lf_next_locked(): Wait until time interrupted.");
    // Sleep was interrupted.  Check for a new next_event.
    // The interruption could also have been due to a call to lf_request_stop().
    next_tag = get_next_event_tag(env);

    // If this (possibly new) next tag is past the stop time, return.
    if (lf_is_tag_after_stop_tag(env, next_tag)) {
      return;
    }
  }
  // A wait occurs even if wait_until() returns true, which means that the
  // tag on the head of the event queue may have changed.
  next_tag = get_next_event_tag(env);

  // If this (possibly new) next tag is past the stop time, return.
  if (lf_is_tag_after_stop_tag(env, next_tag)) { // lf_tag_compare(tag, stop_tag) > 0
    return;
  }

  LF_PRINT_DEBUG("Physical time is ahead of next tag time by " PRINTF_TIME
                 ". This should be small unless -fast is used.",
                 lf_time_physical() - next_tag.time);

#ifdef FEDERATED
  // In federated execution (at least under decentralized coordination),
  // it is possible that an incoming message has been partially read,
  // enough to see its tag. To prevent it from becoming tardy, the thread
  // that is reading the message has set a barrier to prevent logical time
  // from exceeding the timestamp of the message. It will remove that barrier
  // once the complete message has been read. Also, if a federate requests
  // to stop exeuction barriers will used while reaching a consensus.
  // Here, we wait for that barrier to be removed, if appropriate.
  if (_lf_wait_on_tag_barrier(env, next_tag)) {
    // A wait actually occurred, so the next_tag may have changed again.
    next_tag = get_next_event_tag(env);
  }
#endif // FEDERATED

  // If the first event in the event queue has a tag greater than or equal to the
  // stop time, and the current tag matches the stop tag (meaning that we have already
  // executed microstep 0 at the timeout time), then we are done. The above code prevents the next_tag
  // from exceeding the stop_tag, so we have to do further checks if
  // they are equal.
  if (lf_tag_compare(next_tag, env->stop_tag) >= 0 && lf_tag_compare(env->current_tag, env->stop_tag) >= 0) {
    // If we pop anything further off the event queue with this same time or larger,
    // then it will be assigned a tag larger than the stop tag.
    return;
  }

  // At this point, finally, we have an event to process.
  _lf_advance_tag(env, next_tag);

  _lf_start_time_step(env);

  if (lf_tag_compare(env->current_tag, env->stop_tag) >= 0) {
    // Pop shutdown events
    LF_PRINT_DEBUG("Scheduling shutdown reactions.");
    _lf_trigger_shutdown_reactions(env);
  }

  // Pop all events from event_q with timestamp equal to env->current_tag,
  // extract all the reactions triggered by these events, and
  // stick them into the reaction queue.
  _lf_pop_events(env);
#ifdef FEDERATED
  lf_enqueue_port_absent_reactions(env);
  // _lf_pop_events may have set some triggers present.
  extern federate_instance_t _fed;
  lf_update_max_level(_fed.last_TAG, _fed.is_last_TAG_provisional);
#endif
}

/**
 * @brief True if stop has been requested so it doesn't get re-requested.
 */
bool lf_stop_requested = false;

// See reactor.h for docs.
void lf_request_stop(void) {
  // If a requested stop is pending, return without doing anything.
  LF_PRINT_LOG("lf_request_stop() has been called.");
  LF_MUTEX_LOCK(&global_mutex);
  if (lf_stop_requested) {
    LF_MUTEX_UNLOCK(&global_mutex);
    LF_PRINT_LOG("Ignoring redundant lf_request_stop() call.");
    return;
  }
  lf_stop_requested = true;
  LF_MUTEX_UNLOCK(&global_mutex);

  // Iterate over scheduling enclaves to find their maximum current tag
  // and set a barrier for tag advancement for each enclave.
  tag_t max_current_tag = NEVER_TAG;
  environment_t* env;
  int num_environments = _lf_get_environments(&env);
  for (int i = 0; i < num_environments; i++) {
    LF_MUTEX_LOCK(&env[i].mutex);
    if (lf_tag_compare(env[i].current_tag, max_current_tag) > 0) {
      max_current_tag = env[i].current_tag;
    }
    // Set a barrier to prevent the enclave from advancing past the so-far maximum current tag.
    _lf_increment_tag_barrier_locked(&env[i], max_current_tag);
    LF_MUTEX_UNLOCK(&env[i].mutex);
  }

#ifdef FEDERATED
  // In the federated case, the RTI might grant a
  // later stop tag than the current tag. The above code has raised
  // a barrier no greater than max_current_tag.
  if (lf_send_stop_request_to_rti(max_current_tag) != 0) {
    // Message was not sent to the RTI.
    // Decrement the barriers to reverse our previous increment.
    for (int i = 0; i < num_environments; i++) {
      LF_MUTEX_LOCK(&env[i].mutex);
      _lf_decrement_tag_barrier_locked(&env[i]);
      LF_MUTEX_UNLOCK(&env[i].mutex);
    }
  }
#else
  // In a non-federated program, the stop_tag will be the next microstep after max_current_tag.
  // Iterate over environments to set their stop tag and release their barrier.
  for (int i = 0; i < num_environments; i++) {
    LF_MUTEX_LOCK(&env[i].mutex);
    lf_set_stop_tag(&env[i], (tag_t){.time = max_current_tag.time, .microstep = max_current_tag.microstep + 1});
    // Release the barrier on tag advancement.
    _lf_decrement_tag_barrier_locked(&env[i]);

    // We signal instead of broadcast under the assumption that only
    // one worker thread can call wait_until at a given time because
    // the call to wait_until is protected by a mutex lock
    lf_cond_signal(&env->event_q_changed);
    LF_MUTEX_UNLOCK(&env[i].mutex);
  }
#endif
}

void _lf_trigger_reaction(environment_t* env, reaction_t* reaction, int worker_number) {
  assert(env != GLOBAL_ENVIRONMENT);

#ifdef MODAL_REACTORS
  // Check if reaction is disabled by mode inactivity
  if (_lf_mode_is_active(reaction->mode)) {
#endif
    lf_scheduler_trigger_reaction(env->scheduler, reaction, worker_number);
#ifdef MODAL_REACTORS
  } else { // Suppress reaction by preventing entering reaction queue
    LF_PRINT_DEBUG("Suppressing downstream reaction %s due inactivity of mode %s.", reaction->name,
                   reaction->mode->name);
  }
#endif
}

/**
 * Perform the necessary operations before tag (0,0) can be processed.
 *
 * This includes injecting any reactions triggered at (0,0), initializing timers,
 * and for the federated execution, waiting for a proper coordinated start.
 *
 * This assumes the mutex lock is held by the caller.
 * @param env Environment within which we are executing.
 */
static void _lf_initialize_start_tag(environment_t* env) {
  assert(env != GLOBAL_ENVIRONMENT);

  // Add reactions invoked at tag (0,0) (including startup reactions) to the reaction queue
  _lf_trigger_startup_reactions(env);

#if defined FEDERATED
  // If env is the environment for the top-level enclave, then initialize the federate.
  environment_t* top_level_env;
  _lf_get_environments(&top_level_env);
  if (env == top_level_env) {
    // Reset status fields before talking to the RTI to set network port
    // statuses to unknown
    lf_reset_status_fields_on_input_port_triggers();

    // Get a start_time from the RTI
    lf_synchronize_with_other_federates(); // Resets start_time in federated execution according to the RTI.
  }

  // The start time will likely have changed. Adjust the current tag and stop tag.
  env->current_tag = (tag_t){.time = start_time, .microstep = 0u};
  if (duration >= 0LL) {
    // A duration has been specified. Recalculate the stop time.
    env->stop_tag = ((tag_t){.time = start_time + duration, .microstep = 0});
  }

#if defined FEDERATED_DECENTRALIZED
  bool timers_triggered_at_start = _lf_initialize_timers(env);

  // If we have a non-zero STA offset, then we need to allow messages to arrive
  // at the start time.  To avoid spurious STP violations, we temporarily
  // set the current time back by the STA offset.
  env->current_tag.time = lf_time_subtract(env->current_tag.time, lf_fed_STA_offset);
#else
  _lf_initialize_timers(env);
  // For other than federated decentralized execution, there is no lf_fed_STA_offset variable defined.
  // To use uniform code below, we define it here as a local variable.
  instant_t lf_fed_STA_offset = 0;
#endif
  LF_PRINT_LOG("Waiting for start time " PRINTF_TIME ".", start_time);

  // Wait until the start time. This is required for federates because the startup procedure
  // in lf_synchronize_with_other_federates() can decide on a new start_time that is
  // larger than the current physical time.
  // This wait_until() is deliberately called after most precursor operations
  // for tag (0,0) are performed (e.g., injecting startup reactions, etc.).
  // This has two benefits: First, the startup overheads will reduce
  // the required waiting time. Second, this call releases the mutex lock and allows
  // other threads (specifically, federate threads that handle incoming p2p messages
  // from other federates) to hold the lock and possibly raise a tag barrier.
  while (!wait_until(start_time, &env->event_q_changed)) {
  };
  LF_PRINT_DEBUG("Done waiting for start time + STA offset " PRINTF_TIME ".", start_time + lf_fed_STA_offset);
  LF_PRINT_DEBUG("Physical time is ahead of current time by " PRINTF_TIME ". This should be close to the STA offset.",
                 lf_time_physical() - start_time);

  // Restore the current tag to match the start time.
  env->current_tag = (tag_t){.time = start_time, .microstep = 0u};

  // If the stop_tag is (0,0), also insert the shutdown
  // reactions. This can only happen if the timeout time
  // was set to 0.
  if (lf_tag_compare(env->current_tag, env->stop_tag) >= 0) {
    _lf_trigger_shutdown_reactions(env);
  }

#ifdef FEDERATED_DECENTRALIZED
  // In federated execution (at least under decentralized coordination),
  // it is possible that an incoming message has been partially read at (0,0),
  // enough to see its tag. To prevent it from becoming tardy, the thread
  // that is reading the message has set a barrier to prevent logical time
  // from exceeding the timestamp of the message. It will remove that barrier
  // once the complete message has been read. Here, we wait for that barrier
  // to be removed, if appropriate before proceeding to executing tag (0,0).
  _lf_wait_on_tag_barrier(env, (tag_t){.time = start_time, .microstep = 0});

  // In addition, if the earliest event on the event queue has a tag greater
  // than (0,0), then wait until the time of that tag. This prevents the runtime
  // from committing to a start time and then assuming inputs are absent.
  // Do this only if there are no startup reactions.
  if (!timers_triggered_at_start && env->startup_reactions_size == 0) {
    // There are no startup reactions, so we can wait for the earliest event on the event queue.
    tag_t next_tag = get_next_event_tag(env);
    if (next_tag.time > start_time) {
      while (!wait_until(next_tag.time, &env->event_q_changed)) {
        // Did not wait the full time. Check for a new next_tag.
        next_tag = get_next_event_tag(env);
      }
    }
  }

  lf_spawn_staa_thread();

#else  // NOT FEDERATED_DECENTRALIZED
  // Each federate executes the start tag (which is the current
  // tag). Inform the RTI of this if needed.
  send_next_event_tag(env, env->current_tag, true);
#endif // NOT FEDERATED_DECENTRALIZED

  // For messages that may have arrived while we were waiting, put
  // reactions on the reaction queue.
  _lf_pop_events(env);

#else  // NOT FEDERATED
  _lf_initialize_timers(env);

  // If the stop_tag is (0,0), also insert the shutdown
  // reactions. This can only happen if the timeout time
  // was set to 0.
  if (lf_tag_compare(env->current_tag, env->stop_tag) >= 0) {
    _lf_trigger_shutdown_reactions(env);
  }
#endif // NOT FEDERATED

  // Set the following boolean so that other thread(s), including federated threads,
  // know that the execution has started
  env->execution_started = true;
}

/** For logging and debugging, each worker thread is numbered. */
int worker_thread_count = 0;

/**
 * Handle deadline violation for 'reaction'.
 * The mutex should NOT be locked when this function is called. It might acquire
 * the mutex when scheduling the reactions that are triggered as a result of
 * executing the deadline violation handler on the 'reaction', if it exists.
 * @param env Environment within which we are executing.
 * @param worker_number The ID of the worker.
 * @param reaction The reaction whose deadline has been violated.
 *
 * @return true if a deadline violation occurred. false otherwise.
 */
static bool _lf_worker_handle_deadline_violation_for_reaction(environment_t* env, int worker_number,
                                                              reaction_t* reaction) {
  assert(env != GLOBAL_ENVIRONMENT);

  bool violation_occurred = false;
  // If the reaction has a deadline, compare to current physical time
  // and invoke the deadline violation reaction instead of the reaction function
  // if a violation has occurred. Note that the violation reaction will be invoked
  // at most once per logical time value. If the violation reaction triggers the
  // same reaction at the current time value, even if at a future superdense time,
  // then the reaction will be invoked and the violation reaction will not be invoked again.
  if (reaction->deadline >= 0LL) {
    // Get the current physical time.
    instant_t physical_time = lf_time_physical();
    // Check for deadline violation.
    if (reaction->deadline == 0 || physical_time > env->current_tag.time + reaction->deadline) {
      // Deadline violation has occurred.
      tracepoint_reaction_deadline_missed(env, reaction, worker_number);
      violation_occurred = true;
      // Invoke the local handler, if there is one.
      tracepoint_reaction_starts(env, reaction, worker_number);
      reaction_function_t handler = reaction->deadline_violation_handler;
      if (handler != NULL) {
        LF_PRINT_LOG("Worker %d: Deadline violation. Invoking deadline handler.", worker_number);
        (*handler)(reaction->self);

        // If the reaction produced outputs, put the resulting
        // triggered reactions into the queue or execute them directly if possible.
        schedule_output_reactions(env, reaction, worker_number);
        // Remove the reaction from the executing queue.
      }
      tracepoint_reaction_ends(env, reaction, worker_number);
    }
  }
  return violation_occurred;
}

/**
 * Handle STP violation for 'reaction'.
 * The mutex should NOT be locked when this function is called. It might acquire
 * the mutex when scheduling the reactions that are triggered as a result of
 * executing the STP violation handler on the 'reaction', if it exists.
 * @param env Environment within which we are executing.
 * @param worker_number The ID of the worker.
 * @param reaction The reaction whose STP offset has been violated.
 *
 * @return true if an STP violation occurred and was handled. false otherwise.
 */
static bool _lf_worker_handle_STP_violation_for_reaction(environment_t* env, int worker_number, reaction_t* reaction) {
  bool violation_occurred = false;
  // If the reaction violates the STP offset,
  // an input trigger to this reaction has been triggered at a later
  // logical time than originally anticipated. In this case, a special
  // STP handler will be invoked.
  // FIXME: Note that the STP handler will be invoked
  // at most once per logical time value. If the STP handler triggers the
  // same reaction at the current time value, even if at a future superdense time,
  // then the reaction will be invoked and the STP handler will not be invoked again.
  // However, inputs ports to a federate reactor are network port types so this possibly should
  // be disallowed.
  // @note The STP handler and the deadline handler are not mutually exclusive.
  //  In other words, both can be invoked for a reaction if it is triggered late
  //  in logical time (STP offset is violated) and also misses the constraint on
  //  physical time (deadline).
  // @note In absence of an STP handler, the is_STP_violated will be passed down the reaction
  //  chain until it is dealt with in a downstream STP handler.
  if (reaction->is_STP_violated == true && !reaction->is_an_input_reaction) {
    reaction_function_t handler = reaction->STP_handler;
    LF_PRINT_LOG("STP violation detected.");

    // Invoke the STP handler if there is one.
    if (handler != NULL) {
      LF_PRINT_LOG("Worker %d: Invoking STP violation handler.", worker_number);
      // There is a violation
      violation_occurred = true;
      (*handler)(reaction->self);

      // Reset the STP violation flag because it has been dealt with.
      // Downstream handlers should not be invoked.
      reaction->is_STP_violated = false;

      // If the reaction produced outputs, put the resulting
      // triggered reactions into the queue or execute them directly if possible.
      schedule_output_reactions(env, reaction, worker_number);

      // Reset the is_STP_violated because it has been dealt with
      reaction->is_STP_violated = false;
    } else {
      // The intended tag cannot be respected and there is no handler.
      // Print an error message and return true.
      // NOTE: STP violations are ignored for network input reactions, which need to
      // execute anyway.
      lf_print_error("STP violation occurred in a trigger to reaction %d, "
                     "and there is no handler.\n**** Invoking reaction at the wrong tag!",
                     reaction->number + 1); // +1 to align with diagram numbering.
    }
  }
  return violation_occurred;
}

/**
 * Handle violations for 'reaction'. Currently limited to deadline violations
 * and STP violations.
 * The mutex should NOT be locked when this function is called. It might acquire
 * the mutex when scheduling the reactions that are triggered as a result of
 * executing the deadline or STP violation handler(s) on the 'reaction', if they
 * exist.
 * @param env Environment within which we are executing.
 * @param worker_number The ID of the worker.
 * @param reaction The reaction.
 *
 * @return true if a violation occurred and was handled. false otherwise.
 */
static bool _lf_worker_handle_violations(environment_t* env, int worker_number, reaction_t* reaction) {
  bool violation = false;

  violation = _lf_worker_handle_STP_violation_for_reaction(env, worker_number, reaction) ||
              _lf_worker_handle_deadline_violation_for_reaction(env, worker_number, reaction);
  return violation;
}

/**
 * Invoke 'reaction' and schedule any resulting triggered reaction(s) on the
 * reaction queue.
 * The mutex should NOT be locked when this function is called. It might acquire
 * the mutex when scheduling the reactions that are triggered as a result of
 * executing 'reaction'.
 * @param env Environment within which we are executing.
 * @param worker_number The ID of the worker.
 * @param reaction The reaction to invoke.
 */
static void _lf_worker_invoke_reaction(environment_t* env, int worker_number, reaction_t* reaction) {
  LF_PRINT_LOG("Worker %d: Invoking reaction %s at elapsed tag " PRINTF_TAG ".", worker_number, reaction->name,
               env->current_tag.time - start_time, env->current_tag.microstep);
  _lf_invoke_reaction(env, reaction, worker_number);

  // If the reaction produced outputs, put the resulting triggered
  // reactions into the queue or execute them immediately.
  schedule_output_reactions(env, reaction, worker_number);

  reaction->is_STP_violated = false;
}

/**
 * @brief The main looping logic of each LF worker thread.
 *
 * This function returns when the scheduler's lf_sched_get_ready_reaction()
 * implementation returns NULL, indicating that there are no more reactions to execute.
 *
 * This function assumes the caller does not hold the mutex lock on the environment.
 *
 * @param env Environment within which we are executing.
 * @param worker_number The number assigned to this worker thread
 */
static void _lf_worker_do_work(environment_t* env, int worker_number) {
  assert(env != GLOBAL_ENVIRONMENT);

  // Keep track of whether we have decremented the idle thread count.
  // Obtain a reaction from the scheduler that is ready to execute
  // (i.e., it is not blocked by concurrently executing reactions
  // that it depends on).
  // lf_print_snapshot(); // This is quite verbose (but very useful in debugging reaction deadlocks).
  reaction_t* current_reaction_to_execute = NULL;
#ifdef FEDERATED
  lf_stall_advance_level_federation(env, 0);
#endif
  while ((current_reaction_to_execute = lf_sched_get_ready_reaction(env->scheduler, worker_number)) != NULL) {
    // Got a reaction that is ready to run.
    LF_PRINT_DEBUG("Worker %d: Got from scheduler reaction %s: "
                   "level: %lld, is input reaction: %d, and deadline " PRINTF_TIME ".",
                   worker_number, current_reaction_to_execute->name, LF_LEVEL(current_reaction_to_execute->index),
                   current_reaction_to_execute->is_an_input_reaction, current_reaction_to_execute->deadline);

#ifdef FEDERATED_CENTRALIZED
    if (current_reaction_to_execute->is_an_input_reaction) {
      // This federate has received a tagged message with the current tag and
      // must send LTC at the current tag to confirm that the federate has successfully
      // received and processed tagged messages with the current tag.
      env->need_to_send_LTC = true;
    }
#endif // FEDERATED_CENTRALIZED

    bool violation = _lf_worker_handle_violations(env, worker_number, current_reaction_to_execute);

    if (!violation) {
      // Invoke the reaction function.
      _lf_worker_invoke_reaction(env, worker_number, current_reaction_to_execute);
    }

    LF_PRINT_DEBUG("Worker %d: Done with reaction %s.", worker_number, current_reaction_to_execute->name);

    lf_sched_done_with_reaction(worker_number, current_reaction_to_execute);
  }
}

/**
 * Worker thread for the thread pool. Its argument is the environment within which is working
 * The very first worker per environment/enclave is in charge of synchronizing with
 * the other enclaves by getting a TAG to (0,0) this might block until upstream enclaves
 * have finished tag (0,0). This is unlike federated scheduling where each federate will
 * get a PTAG to (0,0) and use network control reactions to handle upstream dependencies
 * @param arg Environment within which the worker should execute.
 */
static void* worker(void* arg) {
  initialize_lf_thread_id();
  environment_t* env = (environment_t*)arg;
  LF_MUTEX_LOCK(&env->mutex);

  int worker_number = env->worker_thread_count++;
  LF_PRINT_LOG("Environment %u: Worker thread %d started.", env->id, worker_number);

// If we have scheduling enclaves. The first worker will block here until
// it receives a TAG for tag (0,0) from the local RTI. In federated scheduling
// we use PTAGs to get things started on tag (0,0) but those are not used
// with enclaves.
#if defined LF_ENCLAVES
  if (worker_number == 0) {
    // If we have scheduling enclaves. We must get a TAG to the start tag.
    LF_PRINT_LOG("Environment %u: Worker thread %d waits for TAG to (0,0).", env->id, worker_number);

    tag_t tag_granted = rti_next_event_tag_locked(env->enclave_info, env->current_tag);
    LF_ASSERT(lf_tag_compare(tag_granted, env->current_tag) == 0, "We did not receive a TAG to the start tag.");
  }
#endif

  // Release mutex and start working.
  LF_MUTEX_UNLOCK(&env->mutex);
  _lf_worker_do_work(env, worker_number);
  LF_MUTEX_LOCK(&env->mutex);

  // This thread is exiting, so don't count it anymore.
  env->worker_thread_count--;

  if (env->worker_thread_count == 0) {
    // The last worker thread to exit will inform the RTI if needed.
#if defined LF_ENCLAVES
    // If we have scheduling enclaves. Then we must send a LTC of FOREVER.
    // to grant other enclaves a TAG to FOREVER.
    // TODO: Can we unify this? Preferraby also have federates send NETs
    rti_logical_tag_complete_locked(env->enclave_info, FOREVER_TAG);
#else
    // In federated execution we send a NET to the RTI. This will result in
    // giving the other federates a PTAG to FOREVER.
    send_next_event_tag(env, FOREVER_TAG, false);
#endif
  }

  lf_cond_signal(&env->event_q_changed);

  LF_PRINT_DEBUG("Worker %d: Stop requested. Exiting.", worker_number);
  LF_MUTEX_UNLOCK(&env->mutex);
  // timeout has been requested.
  return NULL;
}

#ifndef NDEBUG
void lf_print_snapshot(environment_t* env) {
  assert(env != GLOBAL_ENVIRONMENT);

  if (LOG_LEVEL > LOG_LEVEL_LOG) {
    LF_PRINT_DEBUG(">>> START Snapshot");
    LF_PRINT_DEBUG("Pending:");
    // pqueue_dump(reaction_q, print_reaction); FIXME: reaction_q is not
    // accessible here
    LF_PRINT_DEBUG("Event queue size: %zu. Contents:", pqueue_tag_size(env->event_q));
    // FIXME: There is no pqueue_tag_dump now
    pqueue_tag_dump(env->event_q);
    LF_PRINT_DEBUG(">>> END Snapshot");
  }
}
#else  // NDEBUG
void lf_print_snapshot(environment_t* env) {
  (void)env;
  // Do nothing.
}
#endif // NDEBUG

/**
 * @brief Determine the number of workers.
 */
static void determine_number_of_workers(void) {
  // If _lf_number_of_workers is 0, it means that it was not provided on
  // the command-line using the --workers argument.
  if (_lf_number_of_workers == 0u) {
#if !defined(NUMBER_OF_WORKERS) || NUMBER_OF_WORKERS == 0
    // Use the number of cores on the host machine.
    _lf_number_of_workers = lf_available_cores();

// If reaction graph breadth is available. Cap number of workers
#if defined(LF_REACTION_GRAPH_BREADTH)
    if (LF_REACTION_GRAPH_BREADTH < _lf_number_of_workers) {
      _lf_number_of_workers = LF_REACTION_GRAPH_BREADTH;
    }
#endif

#else
    // Use the provided number of workers by the user
    _lf_number_of_workers = NUMBER_OF_WORKERS;
#endif
  }
}

/**
 * The main loop of the LF program.
 *
 * An unambiguous function name that can be called
 * by external libraries.
 *
 * Note: In target languages that use the C core library,
 * there should be an unambiguous way to execute the LF
 * program's main function that will not conflict with
 * other main functions that might get resolved and linked
 * at compile time.
 */
int lf_reactor_c_main(int argc, const char* argv[]) {
  initialize_lf_thread_id();
  // Invoke the function that optionally provides default command-line options.
  lf_set_default_command_line_options();

  // Parse command line arguments. Sets global variables like duration, fast, number_of_workers.
  if (!(process_args(default_argc, default_argv) && process_args(argc, argv))) {
    return -1;
  }

  // Register the termination function
  if (atexit(termination) != 0) {
    lf_print_warning("Failed to register termination function!");
  }
  // The above handles only "normal" termination (via a call to exit).
  // As a consequence, we need to also trap ctrl-C, which issues a SIGINT,
  // and cause it to call exit.
  signal(SIGINT, exit);
#ifdef SIGPIPE
  // Ignore SIGPIPE errors, which terminate the entire application if
  // socket write() fails because the reader has closed the socket.
  // Instead, cause an EPIPE error to be set when write() fails.
  // NOTE: The reason for a broken socket causing a SIGPIPE signal
  // instead of just having write() return an error is to robutly
  // a foo | bar pipeline where bar crashes. The default behavior
  // is for foo to also exit.
  signal(SIGPIPE, SIG_IGN);
#endif // SIGPIPE

  // Determine global number of workers based on user request and available parallelism
  determine_number_of_workers();

  // Initialize the clock through the platform API. No reading of physical time before this.
  _lf_initialize_clock();
  start_time = lf_time_physical();
#ifndef FEDERATED
  lf_tracing_set_start_time(start_time);
#endif

  LF_PRINT_DEBUG("Start time: " PRINTF_TIME "ns", start_time);

#ifdef MINIMAL_STDLIB
  lf_print("---- Start execution ----");
#else
  struct timespec physical_time_timespec = {start_time / BILLION, start_time % BILLION};
  struct tm* time_info = localtime(&physical_time_timespec.tv_sec);
  char buffer[80]; // Long enough to hold the formatted time string.
  // Use strftime rather than ctime because as of C23, ctime is deprecated.
  strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", time_info);

  lf_print("---- Start execution on %s ---- plus %ld nanoseconds", buffer, physical_time_timespec.tv_nsec);
#endif // MINIMAL_STDLIB

  // Create and initialize the environments for each enclave
  lf_create_environments();

  // Initialize the one global mutex
  LF_MUTEX_INIT(&global_mutex);

  // Initialize the global payload and token allocation counts and the trigger table
  // as well as starting tracing subsystem
  initialize_global();

  environment_t* envs;
  int num_envs = _lf_get_environments(&envs);

#if defined LF_ENCLAVES
  initialize_local_rti(envs, num_envs);
#endif

  // Do environment-specific setup
  for (int i = 0; i < num_envs; i++) {
    environment_t* env = &envs[i];

    // Initialize the watchdogs on this environment.
    _lf_initialize_watchdogs(env);

    // Initialize the start and stop tags of the environment
    environment_init_tags(env, start_time, duration);
#ifdef MODAL_REACTORS
    // Set up modal infrastructure
    _lf_initialize_modes(env);
#endif

    // Initialize the scheduler
    // FIXME: Why is this called here and in `_lf_initialize_trigger objects`?
    lf_sched_init(env, (size_t)env->num_workers, NULL);

    // Lock mutex and spawn threads. This must be done before `_lf_initialize_start_tag` since it is using
    //  a cond var
    LF_MUTEX_LOCK(&env->mutex);

    // Initialize start tag
    lf_print("Environment %u: ---- Intializing start tag", env->id);
    _lf_initialize_start_tag(env);

    lf_print("Environment %u: ---- Spawning %d workers.", env->id, env->num_workers);

    for (int j = 0; j < env->num_workers; j++) {
      if (i == 0 && j == 0) {
        // The first worker thread of the first environment will be
        // run on the main thread, rather than creating a new thread.
        // This is important for bare-metal platforms, who can't
        // afford to have the main thread sit idle.
        env->thread_ids[j] = lf_thread_self();
        continue;
      }
      if (lf_thread_create(&env->thread_ids[j], worker, env) != 0) {
        lf_print_error_and_exit("Could not start thread-%u", j);
      }
    }

    // Unlock mutex and allow threads proceed
    LF_MUTEX_UNLOCK(&env->mutex);
  }

  // main thread worker (first worker thread of first environment)
  void* main_thread_exit_status = NULL;
  if (num_envs > 0 && envs[0].num_workers > 0) {
    environment_t* env = &envs[0];
    main_thread_exit_status = worker(env);
  }

  for (int i = 0; i < num_envs; i++) {
    // Wait for the worker threads to exit.
    environment_t* env = &envs[i];
    void* worker_thread_exit_status = NULL;
    int ret = 0;
    for (int j = 0; j < env->num_workers; j++) {
      if (i == 0 && j == 0) {
        // main thread worker
        worker_thread_exit_status = main_thread_exit_status;
      } else {
        int failure = lf_thread_join(env->thread_ids[j], &worker_thread_exit_status);
        if (failure) {
          // Windows warns that strerror is deprecated but doesn't define strerror_r.
          // There seems to be no portable replacement.
          lf_print_error("Failed to join thread listening for incoming messages: %s", strerror(failure));
        }
      }
      if (worker_thread_exit_status != NULL) {
        lf_print_error("---- Worker %d reports error code %p", j, worker_thread_exit_status);
        ret = 1;
      }
    }

    if (ret == 0) {
      LF_PRINT_LOG("---- All worker threads exited successfully.");
    }
  }
  _lf_normal_termination = true;
  return 0;
}

int lf_notify_of_event(environment_t* env) {
  assert(env != GLOBAL_ENVIRONMENT);
  return lf_cond_broadcast(&env->event_q_changed);
}

int lf_critical_section_enter(environment_t* env) {
  if (env == GLOBAL_ENVIRONMENT) {
    return lf_mutex_lock(&global_mutex);
  } else {
    return lf_mutex_lock(&env->mutex);
  }
}

int lf_critical_section_exit(environment_t* env) {
  if (env == GLOBAL_ENVIRONMENT) {
    return lf_mutex_unlock(&global_mutex);
  } else {
    return lf_mutex_unlock(&env->mutex);
  }
}
#endif
