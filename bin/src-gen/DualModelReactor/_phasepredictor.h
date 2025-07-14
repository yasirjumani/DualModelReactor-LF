#ifndef _PHASEPREDICTOR_H
#define _PHASEPREDICTOR_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_660915526_H
#define TOP_LEVEL_PREAMBLE_660915526_H
#endif
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    string value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _phasepredictor_features_t;
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
} _phasepredictor_flag_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    string value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _phasepredictor_label_t;
typedef struct {
    struct self_base_t base;
    #line 11 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int step;
#line 54 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_phasepredictor.h"
#line 55 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_phasepredictor.h"
    _phasepredictor_features_t* _lf_features;
    // width of -2 indicates that it is not a multiport.
    int _lf_features_width;
    // Default input (in case it does not get connected)
    _phasepredictor_features_t _lf_default__features;
    _phasepredictor_flag_t _lf_flag;
    int _lf_flag_width;
    _phasepredictor_label_t _lf_label;
    int _lf_label_width;
    reaction_t _lf__reaction_0;
    trigger_t _lf__features;
    reaction_t* _lf__features_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _phasepredictor_self_t;
_phasepredictor_self_t* new__phasepredictor();
#endif // _PHASEPREDICTOR_H
