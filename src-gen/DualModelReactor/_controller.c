#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/Controller.h"
#include "_controller.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _controllerreaction_function_0(void* instance_args) {
    _controller_self_t* self = (_controller_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _controller_scheduleNext_t* scheduleNext = &self->_lf_scheduleNext;
    #line 115 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    scheduleNext->value = 1;
    scheduleNext->is_present = true;
    schedule(scheduleNext, 1);
#line 16 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_controller.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _controllerreaction_function_1(void* instance_args) {
    _controller_self_t* self = (_controller_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _controller_prediction_t* prediction = self->_lf_prediction;
    int prediction_width = self->_lf_prediction_width; SUPPRESS_UNUSED_WARNING(prediction_width);
    _controller_status_t* status = &self->_lf_status;
    _controller_scheduleNext_t* scheduleNext = &self->_lf_scheduleNext;
    #line 122 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    if (prediction->value == 1) {
        self->current_status = 1;
    }
    
    printf(
        "[STATUS] Wafer %d - Final classification: %s\n",
        self->last_wafer,
        self->current_status ? "Abnormal" : "Normal"
    );
    
    status->value = self->current_status;
    status->is_present = true;
    
    // Schedule the next wafer fetch one logical time unit later
    scheduleNext->value = 1;
    scheduleNext->is_present = true;
    schedule(scheduleNext, 1);
    
    self->current_status = 0;
#line 46 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_controller.c"
}
#include "include/api/reaction_macros_undef.h"
_controller_self_t* new__controller() {
    _controller_self_t* self = (_controller_self_t*)lf_new_reactor(sizeof(_controller_self_t));
    // Set input by default to an always absent default input.
    self->_lf_prediction = &self->_lf_default__prediction;
    // Set the default source reactor pointer
    self->_lf_default__prediction._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _controllerreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _controllerreaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last_tag = NEVER_TAG;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    self->_lf__prediction.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__prediction.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__prediction_reactions[0] = &self->_lf__reaction_1;
    self->_lf__prediction.reactions = &self->_lf__prediction_reactions[0];
    self->_lf__prediction.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__prediction.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__prediction.tmplt.type.element_size = sizeof(int);
    return self;
}
