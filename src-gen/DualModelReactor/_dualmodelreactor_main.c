#include "include/api/schedule.h"
#ifdef FEDERATED
#include <string.h>
#endif // FEDERATED
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/DualModelReactor.h"
#include "_dualmodelreactor_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_0(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct neg1 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } neg1;
    struct mon {
        _digitaltwinmonitor_wafer_t* wafer;
    
    } mon;
    struct log {
        _logger_wafer_t* wafer;
    
    } log;
    struct scrap {
        _scraphandler_wafer_t* wafer;
    
    } scrap;
    neg1.wafer_id = &(self->_lf_neg1.wafer_id);
    mon.wafer = &(self->_lf_mon.wafer);
    log.wafer = &(self->_lf_log.wafer);
    scrap.wafer = &(self->_lf_scrap.wafer);
    #line 108 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    if (!self->busy) {
        self->busy = true;
        neg1.wafer_id->value      = self->wafer_id;
        neg1.wafer_id->is_present = true;
        mon.wafer->value          = self->wafer_id; mon.wafer->is_present = true;
        log.wafer->value          = self->wafer_id; log.wafer->is_present = true;
        scrap.wafer->value        = self->wafer_id; scrap.wafer->is_present = true;
    }
#line 43 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_1(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct neg1 {
        _smartpredictor_prediction_t* prediction;
    
    } neg1;
    struct p1 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } p1;
    struct mon {
        _digitaltwinmonitor_p_neg1_t* p_neg1;
    
    } mon;
    struct log {
        _logger_p_neg1_t* p_neg1;
    
    } log;
    struct scrap {
        _scraphandler_p_neg1_t* p_neg1;
    
    } scrap;
    neg1.prediction = self->_lf_neg1.prediction;
    p1.wafer_id = &(self->_lf_p1.wafer_id);
    mon.p_neg1 = &(self->_lf_mon.p_neg1);
    log.p_neg1 = &(self->_lf_log.p_neg1);
    scrap.p_neg1 = &(self->_lf_scrap.p_neg1);
    #line 119 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = neg1.prediction->value;
    mon.p_neg1->value = log.p_neg1->value = scrap.p_neg1->value = v;
    mon.p_neg1->is_present = log.p_neg1->is_present = scrap.p_neg1->is_present = true;
    if (v==0) { p1.wafer_id->value = self->wafer_id; p1.wafer_id->is_present = true; }
    else      { self->busy=false; self->wafer_id++; }
#line 80 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_2(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct p1 {
        _smartpredictor_prediction_t* prediction;
    
    } p1;
    struct p2 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } p2;
    struct mon {
        _digitaltwinmonitor_p1_t* p1;
    
    } mon;
    struct log {
        _logger_p1_t* p1;
    
    } log;
    struct scrap {
        _scraphandler_p1_t* p1;
    
    } scrap;
    p1.prediction = self->_lf_p1.prediction;
    p2.wafer_id = &(self->_lf_p2.wafer_id);
    mon.p1 = &(self->_lf_mon.p1);
    log.p1 = &(self->_lf_log.p1);
    scrap.p1 = &(self->_lf_scrap.p1);
    #line 126 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = p1.prediction->value;
    mon.p1->value = log.p1->value = scrap.p1->value = v;
    mon.p1->is_present = log.p1->is_present = scrap.p1->is_present = true;
    if (v==0) { p2.wafer_id->value = self->wafer_id; p2.wafer_id->is_present = true; }
    else      { self->busy=false; self->wafer_id++; }
#line 117 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_3(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct p2 {
        _smartpredictor_prediction_t* prediction;
    
    } p2;
    struct p4 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } p4;
    struct mon {
        _digitaltwinmonitor_p2_t* p2;
    
    } mon;
    struct log {
        _logger_p2_t* p2;
    
    } log;
    struct scrap {
        _scraphandler_p2_t* p2;
    
    } scrap;
    p2.prediction = self->_lf_p2.prediction;
    p4.wafer_id = &(self->_lf_p4.wafer_id);
    mon.p2 = &(self->_lf_mon.p2);
    log.p2 = &(self->_lf_log.p2);
    scrap.p2 = &(self->_lf_scrap.p2);
    #line 133 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = p2.prediction->value;
    mon.p2->value = log.p2->value = scrap.p2->value = v;
    mon.p2->is_present = log.p2->is_present = scrap.p2->is_present = true;
    if (v==0) { p4.wafer_id->value = self->wafer_id; p4.wafer_id->is_present = true; }
    else      { self->busy=false; self->wafer_id++; }
#line 154 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_4(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct p4 {
        _smartpredictor_prediction_t* prediction;
    
    } p4;
    struct p6 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } p6;
    struct mon {
        _digitaltwinmonitor_p4_t* p4;
    
    } mon;
    struct log {
        _logger_p4_t* p4;
    
    } log;
    struct scrap {
        _scraphandler_p4_t* p4;
    
    } scrap;
    p4.prediction = self->_lf_p4.prediction;
    p6.wafer_id = &(self->_lf_p6.wafer_id);
    mon.p4 = &(self->_lf_mon.p4);
    log.p4 = &(self->_lf_log.p4);
    scrap.p4 = &(self->_lf_scrap.p4);
    #line 140 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = p4.prediction->value;
    mon.p4->value = log.p4->value = scrap.p4->value = v;
    mon.p4->is_present = log.p4->is_present = scrap.p4->is_present = true;
    if (v==0) { p6.wafer_id->value = self->wafer_id; p6.wafer_id->is_present = true; }
    else      { self->busy=false; self->wafer_id++; }
#line 191 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_5(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct p6 {
        _smartpredictor_prediction_t* prediction;
    
    } p6;
    struct p7 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } p7;
    struct mon {
        _digitaltwinmonitor_p6_t* p6;
    
    } mon;
    struct log {
        _logger_p6_t* p6;
    
    } log;
    struct scrap {
        _scraphandler_p6_t* p6;
    
    } scrap;
    p6.prediction = self->_lf_p6.prediction;
    p7.wafer_id = &(self->_lf_p7.wafer_id);
    mon.p6 = &(self->_lf_mon.p6);
    log.p6 = &(self->_lf_log.p6);
    scrap.p6 = &(self->_lf_scrap.p6);
    #line 147 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = p6.prediction->value;
    mon.p6->value = log.p6->value = scrap.p6->value = v;
    mon.p6->is_present = log.p6->is_present = scrap.p6->is_present = true;
    if (v==0) { p7.wafer_id->value = self->wafer_id; p7.wafer_id->is_present = true; }
    else      { self->busy=false; self->wafer_id++; }
#line 228 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_6(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct p7 {
        _smartpredictor_prediction_t* prediction;
    
    } p7;
    struct neg2 {
        _smartpredictor_wafer_id_t* wafer_id;
    
    } neg2;
    struct mon {
        _digitaltwinmonitor_p7_t* p7;
    
    } mon;
    struct log {
        _logger_p7_t* p7;
    
    } log;
    struct scrap {
        _scraphandler_p7_t* p7;
    
    } scrap;
    p7.prediction = self->_lf_p7.prediction;
    neg2.wafer_id = &(self->_lf_neg2.wafer_id);
    mon.p7 = &(self->_lf_mon.p7);
    log.p7 = &(self->_lf_log.p7);
    scrap.p7 = &(self->_lf_scrap.p7);
    #line 154 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = p7.prediction->value;
    mon.p7->value = log.p7->value = scrap.p7->value = v;
    mon.p7->is_present = log.p7->is_present = scrap.p7->is_present = true;
    if (v==0) { neg2.wafer_id->value = self->wafer_id; neg2.wafer_id->is_present = true; }
    else      { self->busy=false; self->wafer_id++; }
#line 265 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _dualmodelreactor_mainreaction_function_7(void* instance_args) {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    struct neg2 {
        _smartpredictor_prediction_t* prediction;
    
    } neg2;
    struct mon {
        _digitaltwinmonitor_p_neg2_t* p_neg2;
    
    } mon;
    struct log {
        _logger_p_neg2_t* p_neg2;
    
    } log;
    struct scrap {
        _scraphandler_p_neg2_t* p_neg2;
    
    } scrap;
    neg2.prediction = self->_lf_neg2.prediction;
    mon.p_neg2 = &(self->_lf_mon.p_neg2);
    log.p_neg2 = &(self->_lf_log.p_neg2);
    scrap.p_neg2 = &(self->_lf_scrap.p_neg2);
    #line 161 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int v = neg2.prediction->value;
    mon.p_neg2->value = log.p_neg2->value = scrap.p_neg2->value = v;
    mon.p_neg2->is_present = log.p_neg2->is_present = scrap.p_neg2->is_present = true;
    self->busy=false;
    self->wafer_id++;
#line 297 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.c"
}
#include "include/api/reaction_macros_undef.h"
_dualmodelreactor_main_main_self_t* new__dualmodelreactor_main() {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)lf_new_reactor(sizeof(_dualmodelreactor_main_main_self_t));
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_neg1_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_neg1.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_neg1.prediction_reactions[0] = &self->_lf__reaction_1;
    self->_lf_neg1.prediction_trigger.reactions = self->_lf_neg1.prediction_reactions;
    self->_lf_neg1.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_neg1.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_neg1.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_mon_width = -2;
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_log_width = -2;
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_scrap_width = -2;
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_p1_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_p1.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_p1.prediction_reactions[0] = &self->_lf__reaction_2;
    self->_lf_p1.prediction_trigger.reactions = self->_lf_p1.prediction_reactions;
    self->_lf_p1.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_p1.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_p1.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_p2_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_p2.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_p2.prediction_reactions[0] = &self->_lf__reaction_3;
    self->_lf_p2.prediction_trigger.reactions = self->_lf_p2.prediction_reactions;
    self->_lf_p2.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_p2.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_p2.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_p4_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_p4.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_p4.prediction_reactions[0] = &self->_lf__reaction_4;
    self->_lf_p4.prediction_trigger.reactions = self->_lf_p4.prediction_reactions;
    self->_lf_p4.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_p4.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_p4.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_p6_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_p6.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_p6.prediction_reactions[0] = &self->_lf__reaction_5;
    self->_lf_p6.prediction_trigger.reactions = self->_lf_p6.prediction_reactions;
    self->_lf_p6.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_p6.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_p6.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_p7_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_p7.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_p7.prediction_reactions[0] = &self->_lf__reaction_6;
    self->_lf_p7.prediction_trigger.reactions = self->_lf_p7.prediction_reactions;
    self->_lf_p7.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_p7.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_p7.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    // Set the _width variable for all cases. This will be -2
    // if the reactor is not a bank of reactors.
    self->_lf_neg2_width = -2;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf_neg2.prediction_trigger.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf_neg2.prediction_reactions[0] = &self->_lf__reaction_7;
    self->_lf_neg2.prediction_trigger.reactions = self->_lf_neg2.prediction_reactions;
    self->_lf_neg2.prediction_trigger.last_tag = NEVER_TAG;
    self->_lf_neg2.prediction_trigger.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf_neg2.prediction_trigger.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _dualmodelreactor_mainreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _dualmodelreactor_mainreaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__reaction_2.number = 2;
    self->_lf__reaction_2.function = _dualmodelreactor_mainreaction_function_2;
    self->_lf__reaction_2.self = self;
    self->_lf__reaction_2.deadline_violation_handler = NULL;
    self->_lf__reaction_2.STP_handler = NULL;
    self->_lf__reaction_2.name = "?";
    self->_lf__reaction_2.mode = NULL;
    self->_lf__reaction_3.number = 3;
    self->_lf__reaction_3.function = _dualmodelreactor_mainreaction_function_3;
    self->_lf__reaction_3.self = self;
    self->_lf__reaction_3.deadline_violation_handler = NULL;
    self->_lf__reaction_3.STP_handler = NULL;
    self->_lf__reaction_3.name = "?";
    self->_lf__reaction_3.mode = NULL;
    self->_lf__reaction_4.number = 4;
    self->_lf__reaction_4.function = _dualmodelreactor_mainreaction_function_4;
    self->_lf__reaction_4.self = self;
    self->_lf__reaction_4.deadline_violation_handler = NULL;
    self->_lf__reaction_4.STP_handler = NULL;
    self->_lf__reaction_4.name = "?";
    self->_lf__reaction_4.mode = NULL;
    self->_lf__reaction_5.number = 5;
    self->_lf__reaction_5.function = _dualmodelreactor_mainreaction_function_5;
    self->_lf__reaction_5.self = self;
    self->_lf__reaction_5.deadline_violation_handler = NULL;
    self->_lf__reaction_5.STP_handler = NULL;
    self->_lf__reaction_5.name = "?";
    self->_lf__reaction_5.mode = NULL;
    self->_lf__reaction_6.number = 6;
    self->_lf__reaction_6.function = _dualmodelreactor_mainreaction_function_6;
    self->_lf__reaction_6.self = self;
    self->_lf__reaction_6.deadline_violation_handler = NULL;
    self->_lf__reaction_6.STP_handler = NULL;
    self->_lf__reaction_6.name = "?";
    self->_lf__reaction_6.mode = NULL;
    self->_lf__reaction_7.number = 7;
    self->_lf__reaction_7.function = _dualmodelreactor_mainreaction_function_7;
    self->_lf__reaction_7.self = self;
    self->_lf__reaction_7.deadline_violation_handler = NULL;
    self->_lf__reaction_7.STP_handler = NULL;
    self->_lf__reaction_7.name = "?";
    self->_lf__reaction_7.mode = NULL;
    self->_lf__tick.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__tick.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__tick_reactions[0] = &self->_lf__reaction_0;
    self->_lf__tick.reactions = &self->_lf__tick_reactions[0];
    self->_lf__tick.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__tick.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__tick.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__tick.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    return self;
}
