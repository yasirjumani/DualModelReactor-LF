#ifndef _MONITOR_H
#define _MONITOR_H
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
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _monitor_s2_flag_t;
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
} _monitor_s2_label_t;
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
} _monitor_s4_flag_t;
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
} _monitor_s4_label_t;
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
} _monitor_s5_flag_t;
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
} _monitor_s5_label_t;
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
} _monitor_s6_flag_t;
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
} _monitor_s6_label_t;
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
} _monitor_s7_flag_t;
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
} _monitor_s7_label_t;
typedef struct {
    struct self_base_t base;
#line 150 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_monitor.h"
#line 151 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_monitor.h"
    _monitor_s2_flag_t* _lf_s2_flag;
    // width of -2 indicates that it is not a multiport.
    int _lf_s2_flag_width;
    // Default input (in case it does not get connected)
    _monitor_s2_flag_t _lf_default__s2_flag;
    _monitor_s2_label_t* _lf_s2_label;
    // width of -2 indicates that it is not a multiport.
    int _lf_s2_label_width;
    // Default input (in case it does not get connected)
    _monitor_s2_label_t _lf_default__s2_label;
    _monitor_s4_flag_t* _lf_s4_flag;
    // width of -2 indicates that it is not a multiport.
    int _lf_s4_flag_width;
    // Default input (in case it does not get connected)
    _monitor_s4_flag_t _lf_default__s4_flag;
    _monitor_s4_label_t* _lf_s4_label;
    // width of -2 indicates that it is not a multiport.
    int _lf_s4_label_width;
    // Default input (in case it does not get connected)
    _monitor_s4_label_t _lf_default__s4_label;
    _monitor_s5_flag_t* _lf_s5_flag;
    // width of -2 indicates that it is not a multiport.
    int _lf_s5_flag_width;
    // Default input (in case it does not get connected)
    _monitor_s5_flag_t _lf_default__s5_flag;
    _monitor_s5_label_t* _lf_s5_label;
    // width of -2 indicates that it is not a multiport.
    int _lf_s5_label_width;
    // Default input (in case it does not get connected)
    _monitor_s5_label_t _lf_default__s5_label;
    _monitor_s6_flag_t* _lf_s6_flag;
    // width of -2 indicates that it is not a multiport.
    int _lf_s6_flag_width;
    // Default input (in case it does not get connected)
    _monitor_s6_flag_t _lf_default__s6_flag;
    _monitor_s6_label_t* _lf_s6_label;
    // width of -2 indicates that it is not a multiport.
    int _lf_s6_label_width;
    // Default input (in case it does not get connected)
    _monitor_s6_label_t _lf_default__s6_label;
    _monitor_s7_flag_t* _lf_s7_flag;
    // width of -2 indicates that it is not a multiport.
    int _lf_s7_flag_width;
    // Default input (in case it does not get connected)
    _monitor_s7_flag_t _lf_default__s7_flag;
    _monitor_s7_label_t* _lf_s7_label;
    // width of -2 indicates that it is not a multiport.
    int _lf_s7_label_width;
    // Default input (in case it does not get connected)
    _monitor_s7_label_t _lf_default__s7_label;
    reaction_t _lf__reaction_0;
    trigger_t _lf__s2_flag;
    reaction_t* _lf__s2_flag_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s2_label;
    reaction_t* _lf__s2_label_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s4_flag;
    reaction_t* _lf__s4_flag_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s4_label;
    reaction_t* _lf__s4_label_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s5_flag;
    reaction_t* _lf__s5_flag_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s5_label;
    reaction_t* _lf__s5_label_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s6_flag;
    reaction_t* _lf__s6_flag_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s6_label;
    reaction_t* _lf__s6_label_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s7_flag;
    reaction_t* _lf__s7_flag_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__s7_label;
    reaction_t* _lf__s7_label_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _monitor_self_t;
_monitor_self_t* new__monitor();
#endif // _MONITOR_H
