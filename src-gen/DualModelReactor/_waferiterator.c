#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/WaferIterator.h"
#include "_waferiterator.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _waferiteratorreaction_function_0(void* instance_args) {
    _waferiterator_self_t* self = (_waferiterator_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    lf_critical_section_enter(self->base.environment);
    // Expose the action struct as a local variable whose name matches the action name.
    _waferiterator_begin_t* begin = &self->_lf_begin;
    // Set the fields of the action struct to match the current trigger.
    begin->is_present = (bool)self->_lf__begin.status;
    begin->has_value = ((self->_lf__begin.tmplt.token) != NULL && (self->_lf__begin.tmplt.token)->value != NULL);
    _lf_replace_template_token((token_template_t*)begin, (self->_lf__begin.tmplt.token));
    lf_critical_section_exit(self->base.environment);
    #line 76 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    #include <stdio.h>
    #include <stdlib.h>
    
    static FILE* fp = NULL;
    if (!fp) {
        fp = popen("python3 src/wafer_iterator.py", "r");
        if (!fp) {
            fprintf(stderr, "[ERROR] Failed to open wafer_iterator.py\n");
            return;
        }
    }
    
    int w, s;
    if (fscanf(fp, "%d,%d\n", &w, &s) != 2) {
        fprintf(stderr, "[INFO] No more wafer-step pairs.\n");
        pclose(fp);
        fp = NULL;
        return;
    }
    
    wafer_id->value = w;
    wafer_id->is_present = true;
    step->value = s;
    step->is_present = true;
#line 44 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_waferiterator.c"
}
#include "include/api/reaction_macros_undef.h"
_waferiterator_self_t* new__waferiterator() {
    _waferiterator_self_t* self = (_waferiterator_self_t*)lf_new_reactor(sizeof(_waferiterator_self_t));
    self->_lf_begin._base.trigger = &self->_lf__begin;
    self->_lf_begin.parent = (self_base_t*)self;
    self->_lf_begin.source_id = -1;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _waferiteratorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__begin.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__begin.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__begin_reactions[0] = &self->_lf__reaction_0;
    self->_lf__begin.reactions = &self->_lf__begin_reactions[0];
    self->_lf__begin.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__begin.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__begin.is_physical = false;
    
    self->_lf__begin.tmplt.type.element_size = 0;
    self->_lf_begin.type.element_size = 0;
    return self;
}
