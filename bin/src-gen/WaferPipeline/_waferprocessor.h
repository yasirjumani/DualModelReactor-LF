#ifndef _WAFERPROCESSOR_H
#define _WAFERPROCESSOR_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1558133170_H
#define TOP_LEVEL_PREAMBLE_1558133170_H
#endif
typedef struct {
    struct self_base_t base;
#line 10 "/workspace/playground-lingua-franca/bin/src-gen/WaferPipeline/_waferprocessor.h"
    #line 15 "/workspace/playground-lingua-franca/WaferPipeline.lf"
    int index;
    #line 16 "/workspace/playground-lingua-franca/WaferPipeline.lf"
    int total;
#line 15 "/workspace/playground-lingua-franca/bin/src-gen/WaferPipeline/_waferprocessor.h"
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__t;
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _waferprocessor_self_t;
_waferprocessor_self_t* new__waferprocessor();
#endif // _WAFERPROCESSOR_H
