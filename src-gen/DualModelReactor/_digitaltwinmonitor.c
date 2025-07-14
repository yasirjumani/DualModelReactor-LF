#include "include/api/schedule.h"
#ifdef FEDERATED
#include <string.h>
#endif // FEDERATED
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/DigitalTwinMonitor.h"
#include "_digitaltwinmonitor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _digitaltwinmonitorreaction_function_0(void* instance_args) {
    _digitaltwinmonitor_self_t* self = (_digitaltwinmonitor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _digitaltwinmonitor_p_neg2_t* p_neg2 = self->_lf_p_neg2;
    int p_neg2_width = self->_lf_p_neg2_width; SUPPRESS_UNUSED_WARNING(p_neg2_width);
    _digitaltwinmonitor_wafer_t* wafer = self->_lf_wafer;
    int wafer_width = self->_lf_wafer_width; SUPPRESS_UNUSED_WARNING(wafer_width);
    _digitaltwinmonitor_p_neg1_t* p_neg1 = self->_lf_p_neg1;
    int p_neg1_width = self->_lf_p_neg1_width; SUPPRESS_UNUSED_WARNING(p_neg1_width);
    _digitaltwinmonitor_p1_t* p1 = self->_lf_p1;
    int p1_width = self->_lf_p1_width; SUPPRESS_UNUSED_WARNING(p1_width);
    _digitaltwinmonitor_p2_t* p2 = self->_lf_p2;
    int p2_width = self->_lf_p2_width; SUPPRESS_UNUSED_WARNING(p2_width);
    _digitaltwinmonitor_p4_t* p4 = self->_lf_p4;
    int p4_width = self->_lf_p4_width; SUPPRESS_UNUSED_WARNING(p4_width);
    _digitaltwinmonitor_p6_t* p6 = self->_lf_p6;
    int p6_width = self->_lf_p6_width; SUPPRESS_UNUSED_WARNING(p6_width);
    _digitaltwinmonitor_p7_t* p7 = self->_lf_p7;
    int p7_width = self->_lf_p7_width; SUPPRESS_UNUSED_WARNING(p7_width);
    #line 61 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    printf("\n[MONITOR] Wafer %d\n", wafer->value);
    printf("  -1:%d  1:%d  2:%d  4:%d  6:%d  7:%d  -2:%d\n",
           p_neg1->value, p1->value, p2->value,
           p4->value, p6->value, p7->value, p_neg2->value);
    int fault = p_neg1->value || p1->value || p2->value ||
                p4->value    || p6->value || p7->value || p_neg2->value;
    printf("  → Final Classification: %s\n", fault ? "ABNORMAL" : "NORMAL");
#line 38 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_digitaltwinmonitor.c"
}
#include "include/api/reaction_macros_undef.h"
_digitaltwinmonitor_self_t* new__digitaltwinmonitor() {
    _digitaltwinmonitor_self_t* self = (_digitaltwinmonitor_self_t*)lf_new_reactor(sizeof(_digitaltwinmonitor_self_t));
    // Set input by default to an always absent default input.
    self->_lf_wafer = &self->_lf_default__wafer;
    // Set the default source reactor pointer
    self->_lf_default__wafer._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p_neg1 = &self->_lf_default__p_neg1;
    // Set the default source reactor pointer
    self->_lf_default__p_neg1._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p1 = &self->_lf_default__p1;
    // Set the default source reactor pointer
    self->_lf_default__p1._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p2 = &self->_lf_default__p2;
    // Set the default source reactor pointer
    self->_lf_default__p2._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p4 = &self->_lf_default__p4;
    // Set the default source reactor pointer
    self->_lf_default__p4._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p6 = &self->_lf_default__p6;
    // Set the default source reactor pointer
    self->_lf_default__p6._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p7 = &self->_lf_default__p7;
    // Set the default source reactor pointer
    self->_lf_default__p7._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_p_neg2 = &self->_lf_default__p_neg2;
    // Set the default source reactor pointer
    self->_lf_default__p_neg2._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _digitaltwinmonitorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__wafer.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__wafer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__wafer_reactions[0] = &self->_lf__reaction_0;
    self->_lf__wafer.reactions = &self->_lf__wafer_reactions[0];
    self->_lf__wafer.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__wafer.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__wafer.tmplt.type.element_size = sizeof(int);
    self->_lf__p_neg1.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p_neg1.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p_neg1_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p_neg1.reactions = &self->_lf__p_neg1_reactions[0];
    self->_lf__p_neg1.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p_neg1.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p_neg1.tmplt.type.element_size = sizeof(int);
    self->_lf__p1.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p1.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p1_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p1.reactions = &self->_lf__p1_reactions[0];
    self->_lf__p1.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p1.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p1.tmplt.type.element_size = sizeof(int);
    self->_lf__p2.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p2.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p2_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p2.reactions = &self->_lf__p2_reactions[0];
    self->_lf__p2.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p2.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p2.tmplt.type.element_size = sizeof(int);
    self->_lf__p4.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p4.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p4_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p4.reactions = &self->_lf__p4_reactions[0];
    self->_lf__p4.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p4.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p4.tmplt.type.element_size = sizeof(int);
    self->_lf__p6.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p6.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p6_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p6.reactions = &self->_lf__p6_reactions[0];
    self->_lf__p6.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p6.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p6.tmplt.type.element_size = sizeof(int);
    self->_lf__p7.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p7.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p7_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p7.reactions = &self->_lf__p7_reactions[0];
    self->_lf__p7.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p7.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p7.tmplt.type.element_size = sizeof(int);
    self->_lf__p_neg2.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__p_neg2.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__p_neg2_reactions[0] = &self->_lf__reaction_0;
    self->_lf__p_neg2.reactions = &self->_lf__p_neg2_reactions[0];
    self->_lf__p_neg2.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__p_neg2.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__p_neg2.tmplt.type.element_size = sizeof(int);
    return self;
}
