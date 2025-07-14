#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/WaferPipeline/WaferPipeline.h"
#include "_waferpipeline_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
_waferpipeline_main_main_self_t* new__waferpipeline_main() {
    _waferpipeline_main_main_self_t* self = (_waferpipeline_main_main_self_t*)lf_new_reactor(sizeof(_waferpipeline_main_main_self_t));

    return self;
}
