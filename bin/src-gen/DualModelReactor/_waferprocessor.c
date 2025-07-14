#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/WaferProcessor.h"
#include "_waferprocessor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _waferprocessorreaction_function_0(void* instance_args) {
    _waferprocessor_self_t* self = (_waferprocessor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 19 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    printf("[WaferProcessor] Initialized\n");
    self->index = 0;
    self->total = 100;  // Simulate 100 wafers
    srand(time(NULL));
#line 17 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_waferprocessor.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _waferprocessorreaction_function_1(void* instance_args) {
    _waferprocessor_self_t* self = (_waferprocessor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 26 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    if (self->index >= self->total) {
        printf("[WaferProcessor] All wafers processed.\n");
        return;
    }
    
    float features[17];
    int is_normal = rand() % 2;
    
    for (int i = 0; i < 17; i++) {
        if (is_normal) {
            features[i] = ((float)(rand() % 100) / 100.0f) + 0.05f;
        } else {
            features[i] = ((float)(rand() % 300) / 100.0f) + 2.0f;
        }
    }
    
    char feature_str[1024] = "";
    for (int i = 0; i < 17; i++) {
        char temp[32];
        snprintf(temp, sizeof(temp), "%.6f ", features[i]);
        strncat(feature_str, temp, sizeof(feature_str) - strlen(feature_str) - 1);
    }
    
    const int steps[4] = {2, 4, 6, 7};
    char preds[4][8];
    int any_abnormal = 0;
    
    for (int i = 0; i < 4; i++) {
        char command[2048];
        snprintf(command, sizeof(command),
            "python3 src/model_predictor.py %d %s", steps[i], feature_str);
    
        FILE* fp = popen(command, "r");
        if (!fp) {
            fprintf(stderr, "Failed to run model for step %d\n", steps[i]);
            strncpy(preds[i], "?", sizeof(preds[i]));
            continue;
        }
    
        char line[128];
        if (!fgets(line, sizeof(line), fp)) {
            fprintf(stderr, "No output for step %d\n", steps[i]);
            strncpy(preds[i], "?", sizeof(preds[i]));
            pclose(fp);
            continue;
        }
    
        fgets(line, sizeof(line), fp); // numeric prediction
        strncpy(preds[i], line, sizeof(preds[i]) - 1);
        preds[i][strcspn(preds[i], "\r\n")] = 0;
    
        if (strcmp(preds[i], "1") == 0) {
            any_abnormal = 1;
        }
    
        pclose(fp);
    }
    
    int target = is_normal ? 0 : 1;
    int final = any_abnormal ? 1 : 0;
    
    FILE* log = fopen("lf_output.log", "a");
    if (log) {
        fprintf(log, "[Decision] Wafer %d | Predictions: [%s, %s, %s, %s] → Final: %d | Target: %d\n",
            self->index + 1, preds[0], preds[1], preds[2], preds[3], final, target);
        fflush(log);
        fclose(log);
    }
    
    printf("[WaferProcessor] Wafer %d → Final: %d | Target: %d\n",
        self->index + 1, final, target);
    
    self->index++;
#line 98 "/workspace/playground-lingua-franca/bin/src-gen/DualModelReactor/_waferprocessor.c"
}
#include "include/api/reaction_macros_undef.h"
_waferprocessor_self_t* new__waferprocessor() {
    _waferprocessor_self_t* self = (_waferprocessor_self_t*)lf_new_reactor(sizeof(_waferprocessor_self_t));
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _waferprocessorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _waferprocessorreaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__t.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__t_reactions[0] = &self->_lf__reaction_1;
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    self->_lf__t.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__t.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last_tag = NEVER_TAG;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    return self;
}
