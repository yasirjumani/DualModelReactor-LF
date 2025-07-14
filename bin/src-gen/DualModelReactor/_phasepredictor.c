#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/PhasePredictor.h"
#include "_phasepredictor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _phasepredictorreaction_function_0(void* instance_args) {
    _phasepredictor_self_t* self = (_phasepredictor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _phasepredictor_features_t* features = self->_lf_features;
    int features_width = self->_lf_features_width; SUPPRESS_UNUSED_WARNING(features_width);
    _phasepredictor_flag_t* flag = &self->_lf_flag;
    _phasepredictor_label_t* label = &self->_lf_label;
    #line 17 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    char command[1024];
    snprintf(command, sizeof(command), "python3 src/model_predictor.py %d %s", self->step, features->value);
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run model_predictor.py for step %d.\n", self->step);
        return;
    }
    
    char line[64];
    if (fgets(line, sizeof(line), pipe)) {
        label->value = strdup(line);
        label->is_present = true;
    }
    
    if (fgets(line, sizeof(line), pipe)) {
        flag->value = atoi(line);
        flag->is_present = true;
    }
    
    pclose(pipe);
#line 37 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_phasepredictor.c"
}
#include "include/api/reaction_macros_undef.h"
_phasepredictor_self_t* new__phasepredictor() {
    _phasepredictor_self_t* self = (_phasepredictor_self_t*)lf_new_reactor(sizeof(_phasepredictor_self_t));
    // Set input by default to an always absent default input.
    self->_lf_features = &self->_lf_default__features;
    // Set the default source reactor pointer
    self->_lf_default__features._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _phasepredictorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__features.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__features.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__features_reactions[0] = &self->_lf__reaction_0;
    self->_lf__features.reactions = &self->_lf__features_reactions[0];
    self->_lf__features.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__features.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__features.tmplt.type.element_size = sizeof(string);
    return self;
}
