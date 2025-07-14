#include "include/api/schedule.h"
#ifdef FEDERATED
#include <string.h>
#endif // FEDERATED
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/SmartPredictor.h"
#include "_smartpredictor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _smartpredictorreaction_function_0(void* instance_args) {
    _smartpredictor_self_t* self = (_smartpredictor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _smartpredictor_wafer_id_t* wafer_id = self->_lf_wafer_id;
    int wafer_id_width = self->_lf_wafer_id_width; SUPPRESS_UNUSED_WARNING(wafer_id_width);
    _smartpredictor_prediction_t* prediction = &self->_lf_prediction;
    #line 15 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    #include <stdio.h>
    #include <stdlib.h>
    int flag = 1;
    char cmd[512];
    snprintf(cmd, sizeof(cmd),
        "python3 src/model_predictor.py %d %d --csv D1.csv --model-dir models --agg %s --threshold %.2f",
        self->step, wafer_id->value, self->agg, self->threshold
    );
    FILE* fp = popen(cmd, "r");
    if (fp) {
        char buf[128];
        // skip label
        fgets(buf, sizeof(buf), fp);
        // read flag
        if (fgets(buf, sizeof(buf), fp)) flag = atoi(buf);
        pclose(fp);
    }
    prediction->value      = flag;
    prediction->is_present = true;
#line 37 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_smartpredictor.c"
}
#include "include/api/reaction_macros_undef.h"
_smartpredictor_self_t* new__smartpredictor() {
    _smartpredictor_self_t* self = (_smartpredictor_self_t*)lf_new_reactor(sizeof(_smartpredictor_self_t));
    // Set input by default to an always absent default input.
    self->_lf_wafer_id = &self->_lf_default__wafer_id;
    // Set the default source reactor pointer
    self->_lf_default__wafer_id._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _smartpredictorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__wafer_id.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__wafer_id.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__wafer_id_reactions[0] = &self->_lf__reaction_0;
    self->_lf__wafer_id.reactions = &self->_lf__wafer_id_reactions[0];
    self->_lf__wafer_id.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__wafer_id.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__wafer_id.tmplt.type.element_size = sizeof(int);
    return self;
}
