#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/Monitor.h"
#include "_monitor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _monitorreaction_function_0(void* instance_args) {
    _monitor_self_t* self = (_monitor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _monitor_s2_flag_t* s2_flag = self->_lf_s2_flag;
    int s2_flag_width = self->_lf_s2_flag_width; SUPPRESS_UNUSED_WARNING(s2_flag_width);
    _monitor_s2_label_t* s2_label = self->_lf_s2_label;
    int s2_label_width = self->_lf_s2_label_width; SUPPRESS_UNUSED_WARNING(s2_label_width);
    _monitor_s4_flag_t* s4_flag = self->_lf_s4_flag;
    int s4_flag_width = self->_lf_s4_flag_width; SUPPRESS_UNUSED_WARNING(s4_flag_width);
    _monitor_s4_label_t* s4_label = self->_lf_s4_label;
    int s4_label_width = self->_lf_s4_label_width; SUPPRESS_UNUSED_WARNING(s4_label_width);
    _monitor_s5_flag_t* s5_flag = self->_lf_s5_flag;
    int s5_flag_width = self->_lf_s5_flag_width; SUPPRESS_UNUSED_WARNING(s5_flag_width);
    _monitor_s5_label_t* s5_label = self->_lf_s5_label;
    int s5_label_width = self->_lf_s5_label_width; SUPPRESS_UNUSED_WARNING(s5_label_width);
    _monitor_s6_flag_t* s6_flag = self->_lf_s6_flag;
    int s6_flag_width = self->_lf_s6_flag_width; SUPPRESS_UNUSED_WARNING(s6_flag_width);
    _monitor_s6_label_t* s6_label = self->_lf_s6_label;
    int s6_label_width = self->_lf_s6_label_width; SUPPRESS_UNUSED_WARNING(s6_label_width);
    _monitor_s7_flag_t* s7_flag = self->_lf_s7_flag;
    int s7_flag_width = self->_lf_s7_flag_width; SUPPRESS_UNUSED_WARNING(s7_flag_width);
    _monitor_s7_label_t* s7_label = self->_lf_s7_label;
    int s7_label_width = self->_lf_s7_label_width; SUPPRESS_UNUSED_WARNING(s7_label_width);
    #line 55 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    printf("Step 2: %s → %d\n", s2_label->value, s2_flag->value);
    printf("Step 4: %s → %d\n", s4_label->value, s4_flag->value);
    printf("Step 5: %s → %d\n", s5_label->value, s5_flag->value);
    printf("Step 6: %s → %d\n", s6_label->value, s6_flag->value);
    printf("Step 7: %s → %d\n", s7_label->value, s7_flag->value);
    int fault = s2_flag->value || s4_flag->value || s5_flag->value || s6_flag->value || s7_flag->value;
    printf("Final Prediction: %d\n", fault);
#line 39 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_monitor.c"
}
#include "include/api/reaction_macros_undef.h"
_monitor_self_t* new__monitor() {
    _monitor_self_t* self = (_monitor_self_t*)lf_new_reactor(sizeof(_monitor_self_t));
    // Set input by default to an always absent default input.
    self->_lf_s2_flag = &self->_lf_default__s2_flag;
    // Set the default source reactor pointer
    self->_lf_default__s2_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s2_label = &self->_lf_default__s2_label;
    // Set the default source reactor pointer
    self->_lf_default__s2_label._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s4_flag = &self->_lf_default__s4_flag;
    // Set the default source reactor pointer
    self->_lf_default__s4_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s4_label = &self->_lf_default__s4_label;
    // Set the default source reactor pointer
    self->_lf_default__s4_label._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s5_flag = &self->_lf_default__s5_flag;
    // Set the default source reactor pointer
    self->_lf_default__s5_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s5_label = &self->_lf_default__s5_label;
    // Set the default source reactor pointer
    self->_lf_default__s5_label._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s6_flag = &self->_lf_default__s6_flag;
    // Set the default source reactor pointer
    self->_lf_default__s6_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s6_label = &self->_lf_default__s6_label;
    // Set the default source reactor pointer
    self->_lf_default__s6_label._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s7_flag = &self->_lf_default__s7_flag;
    // Set the default source reactor pointer
    self->_lf_default__s7_flag._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_s7_label = &self->_lf_default__s7_label;
    // Set the default source reactor pointer
    self->_lf_default__s7_label._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _monitorreaction_function_0;
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
    self->_lf__s2_label.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s2_label.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s2_label_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s2_label.reactions = &self->_lf__s2_label_reactions[0];
    self->_lf__s2_label.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s2_label.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s2_label.tmplt.type.element_size = sizeof(string);
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
    self->_lf__s4_label.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s4_label.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s4_label_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s4_label.reactions = &self->_lf__s4_label_reactions[0];
    self->_lf__s4_label.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s4_label.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s4_label.tmplt.type.element_size = sizeof(string);
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
    self->_lf__s5_label.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s5_label.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s5_label_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s5_label.reactions = &self->_lf__s5_label_reactions[0];
    self->_lf__s5_label.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s5_label.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s5_label.tmplt.type.element_size = sizeof(string);
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
    self->_lf__s6_label.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s6_label.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s6_label_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s6_label.reactions = &self->_lf__s6_label_reactions[0];
    self->_lf__s6_label.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s6_label.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s6_label.tmplt.type.element_size = sizeof(string);
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
    self->_lf__s7_label.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__s7_label.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__s7_label_reactions[0] = &self->_lf__reaction_0;
    self->_lf__s7_label.reactions = &self->_lf__s7_label_reactions[0];
    self->_lf__s7_label.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__s7_label.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__s7_label.tmplt.type.element_size = sizeof(string);
    return self;
}
