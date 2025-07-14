#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/DigitalTwin.h"
#include "_digitaltwin.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _digitaltwinreaction_function_0(void* instance_args) {
    _digitaltwin_self_t* self = (_digitaltwin_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _digitaltwin_s2_flag_t* s2_flag = self->_lf_s2_flag;
    int s2_flag_width = self->_lf_s2_flag_width; SUPPRESS_UNUSED_WARNING(s2_flag_width);
    _digitaltwin_s4_flag_t* s4_flag = self->_lf_s4_flag;
    int s4_flag_width = self->_lf_s4_flag_width; SUPPRESS_UNUSED_WARNING(s4_flag_width);
    _digitaltwin_s5_flag_t* s5_flag = self->_lf_s5_flag;
    int s5_flag_width = self->_lf_s5_flag_width; SUPPRESS_UNUSED_WARNING(s5_flag_width);
    _digitaltwin_s6_flag_t* s6_flag = self->_lf_s6_flag;
    int s6_flag_width = self->_lf_s6_flag_width; SUPPRESS_UNUSED_WARNING(s6_flag_width);
    _digitaltwin_s7_flag_t* s7_flag = self->_lf_s7_flag;
    int s7_flag_width = self->_lf_s7_flag_width; SUPPRESS_UNUSED_WARNING(s7_flag_width);
    _digitaltwin_twinState_t* twinState = &self->_lf_twinState;
    #line 75 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    char buffer[256];
    snprintf(buffer, sizeof(buffer),
        "{\"step2\": %d, \"step4\": %d, \"step5\": %d, \"step6\": %d, \"step7\": %d}",
        s2_flag->value, s4_flag->value, s5_flag->value, s6_flag->value, s7_flag->value);
    twinState->value = strdup(buffer);
    twinState->is_present = true;
    printf("Digital Twin State Updated: %s\n", twinState->value);
#line 30 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_digitaltwin.c"
}
#include "include/api/reaction_macros_undef.h"
_digitaltwin_self_t* new__digitaltwin() {
    _digitaltwin_self_t* self = (_digitaltwin_self_t*)lf_new_reactor(sizeof(_digitaltwin_self_t));
    // Set input by default to an always absent default input.
    self->_lf_s2_flag = &self->_lf_default__s2_flag;
    // Set the default source reactor pointer
    self->_lf_default__s2_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s4_flag = &self->_lf_default__s4_flag;
    // Set the default source reactor pointer
    self->_lf_default__s4_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s5_flag = &self->_lf_default__s5_flag;
    // Set the default source reactor pointer
    self->_lf_default__s5_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s6_flag = &self->_lf_default__s6_flag;
    // Set the default source reactor pointer
    self->_lf_default__s6_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s7_flag = &self->_lf_default__s7_flag;
    // Set the default source reactor pointer
    self->_lf_default__s7_flag._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _digitaltwinreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__s2_flag.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s2_flag.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s2_flag_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s2_flag.reactions = &self->_lf__s2_flag_reactions[0];
    self->_lf__s2_flag.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s2_flag.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s2_flag.tmplt.type.element_size = sizeof(int);
    self->_lf__s4_flag.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s4_flag.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s4_flag_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s4_flag.reactions = &self->_lf__s4_flag_reactions[0];
    self->_lf__s4_flag.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s4_flag.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s4_flag.tmplt.type.element_size = sizeof(int);
    self->_lf__s5_flag.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s5_flag.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s5_flag_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s5_flag.reactions = &self->_lf__s5_flag_reactions[0];
    self->_lf__s5_flag.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s5_flag.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s5_flag.tmplt.type.element_size = sizeof(int);
    self->_lf__s6_flag.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s6_flag.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s6_flag_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s6_flag.reactions = &self->_lf__s6_flag_reactions[0];
    self->_lf__s6_flag.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s6_flag.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s6_flag.tmplt.type.element_size = sizeof(int);
    self->_lf__s7_flag.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s7_flag.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s7_flag_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s7_flag.reactions = &self->_lf__s7_flag_reactions[0];
    self->_lf__s7_flag.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s7_flag.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s7_flag.tmplt.type.element_size = sizeof(int);
    return self;
}
