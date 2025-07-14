#ifndef _smartpredictor_H
#define _smartpredictor_H
#ifndef _SMARTPREDICTOR_H // necessary for arduino-cli, which automatically includes headers that are not used

#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/schedule.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct smartpredictor_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    int step;
    string agg;
    float threshold;
    int end[0]; // placeholder; MSVC does not compile empty structs
} smartpredictor_self_t;
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
} smartpredictor_wafer_id_t;
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
} smartpredictor_prediction_t;
#endif
#endif
