#ifndef _SMARTPREDICTOR_H
#define _SMARTPREDICTOR_H
#include "include/core/reactor.h"

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
} _smartpredictor_wafer_id_t;
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
} _smartpredictor_prediction_t;
typedef struct {
    struct self_base_t base;
    #line 7 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int step;
    #line 8 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    string agg;
    #line 9 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    float threshold;
#line 42 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_smartpredictor.h"
#line 43 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_smartpredictor.h"
    _smartpredictor_wafer_id_t* _lf_wafer_id;
    // width of -2 indicates that it is not a multiport.
    int _lf_wafer_id_width;
    // Default input (in case it does not get connected)
    _smartpredictor_wafer_id_t _lf_default__wafer_id;
    _smartpredictor_prediction_t _lf_prediction;
    int _lf_prediction_width;
    reaction_t _lf__reaction_0;
    trigger_t _lf__wafer_id;
    reaction_t* _lf__wafer_id_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _smartpredictor_self_t;
_smartpredictor_self_t* new__smartpredictor();
#endif // _SMARTPREDICTOR_H
