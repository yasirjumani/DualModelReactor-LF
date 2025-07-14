#ifndef _waferprocessor_H
#define _waferprocessor_H
#ifndef _WAFERPROCESSOR_H // necessary for arduino-cli, which automatically includes headers that are not used
#ifndef TOP_LEVEL_PREAMBLE_1558133170_H
#define TOP_LEVEL_PREAMBLE_1558133170_H
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/schedule.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct waferprocessor_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    int index;
    int total;
    int end[0]; // placeholder; MSVC does not compile empty structs
} waferprocessor_self_t;
#endif
#endif
