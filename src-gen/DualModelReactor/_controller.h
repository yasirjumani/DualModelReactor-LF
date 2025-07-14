#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1876259196_H
#define TOP_LEVEL_PREAMBLE_1876259196_H
#endif
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _controller_prediction_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _controller_scheduleNext_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _controller_status_t;
typedef struct {
    struct self_base_t base;
#line 52 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_controller.h"
    #line 110 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int last_wafer;
    #line 111 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int current_status;
#line 57 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_controller.h"
    _controller_prediction_t* _lf_prediction;
    // width of -2 indicates that it is not a multiport.
    int _lf_prediction_width;
    // Default input (in case it does not get connected)
    _controller_prediction_t _lf_default__prediction;
    _controller_scheduleNext_t _lf_scheduleNext;
    int _lf_scheduleNext_width;
    _controller_status_t _lf_status;
    int _lf_status_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
    trigger_t _lf__prediction;
    reaction_t* _lf__prediction_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _controller_self_t;
_controller_self_t* new__controller();
#endif // _CONTROLLER_H
