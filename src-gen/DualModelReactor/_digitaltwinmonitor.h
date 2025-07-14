#ifndef _DIGITALTWINMONITOR_H
#define _DIGITALTWINMONITOR_H
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
} _digitaltwinmonitor_wafer_t;
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
} _digitaltwinmonitor_p_neg1_t;
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
} _digitaltwinmonitor_p1_t;
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
} _digitaltwinmonitor_p2_t;
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
} _digitaltwinmonitor_p4_t;
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
} _digitaltwinmonitor_p6_t;
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
} _digitaltwinmonitor_p7_t;
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
} _digitaltwinmonitor_p_neg2_t;
typedef struct {
    struct self_base_t base;
#line 120 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_digitaltwinmonitor.h"
#line 121 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_digitaltwinmonitor.h"
    _digitaltwinmonitor_wafer_t* _lf_wafer;
    // width of -2 indicates that it is not a multiport.
    int _lf_wafer_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_wafer_t _lf_default__wafer;
    _digitaltwinmonitor_p_neg1_t* _lf_p_neg1;
    // width of -2 indicates that it is not a multiport.
    int _lf_p_neg1_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p_neg1_t _lf_default__p_neg1;
    _digitaltwinmonitor_p1_t* _lf_p1;
    // width of -2 indicates that it is not a multiport.
    int _lf_p1_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p1_t _lf_default__p1;
    _digitaltwinmonitor_p2_t* _lf_p2;
    // width of -2 indicates that it is not a multiport.
    int _lf_p2_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p2_t _lf_default__p2;
    _digitaltwinmonitor_p4_t* _lf_p4;
    // width of -2 indicates that it is not a multiport.
    int _lf_p4_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p4_t _lf_default__p4;
    _digitaltwinmonitor_p6_t* _lf_p6;
    // width of -2 indicates that it is not a multiport.
    int _lf_p6_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p6_t _lf_default__p6;
    _digitaltwinmonitor_p7_t* _lf_p7;
    // width of -2 indicates that it is not a multiport.
    int _lf_p7_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p7_t _lf_default__p7;
    _digitaltwinmonitor_p_neg2_t* _lf_p_neg2;
    // width of -2 indicates that it is not a multiport.
    int _lf_p_neg2_width;
    // Default input (in case it does not get connected)
    _digitaltwinmonitor_p_neg2_t _lf_default__p_neg2;
    reaction_t _lf__reaction_0;
    trigger_t _lf__wafer;
    reaction_t* _lf__wafer_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p_neg1;
    reaction_t* _lf__p_neg1_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p1;
    reaction_t* _lf__p1_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p2;
    reaction_t* _lf__p2_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p4;
    reaction_t* _lf__p4_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p6;
    reaction_t* _lf__p6_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p7;
    reaction_t* _lf__p7_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__p_neg2;
    reaction_t* _lf__p_neg2_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _digitaltwinmonitor_self_t;
_digitaltwinmonitor_self_t* new__digitaltwinmonitor();
#endif // _DIGITALTWINMONITOR_H
