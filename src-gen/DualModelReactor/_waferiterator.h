#ifndef _WAFERITERATOR_H
#define _WAFERITERATOR_H
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
} _waferiterator_wafer_id_t;
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
} _waferiterator_step_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_action_internal_t _base;
    self_base_t* parent;
    bool has_value;
    int source_id;

    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _waferiterator_begin_t;
typedef struct {
    struct self_base_t base;
#line 55 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_waferiterator.h"
#line 56 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_waferiterator.h"
    _waferiterator_begin_t _lf_begin;
    _waferiterator_wafer_id_t _lf_wafer_id;
    int _lf_wafer_id_width;
    _waferiterator_step_t _lf_step;
    int _lf_step_width;
    reaction_t _lf__reaction_0;
    trigger_t _lf__begin;
    reaction_t* _lf__begin_reactions[1];
} _waferiterator_self_t;
_waferiterator_self_t* new__waferiterator();
#endif // _WAFERITERATOR_H
