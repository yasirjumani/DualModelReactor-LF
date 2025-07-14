#include "include/api/schedule.h"
#include "low_level_platform/api/low_level_platform.h"
#include "include/DualModelReactor/DualModelReactor.h"
#include "_dualmodelreactor_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
_dualmodelreactor_main_main_self_t* new__dualmodelreactor_main() {
    _dualmodelreactor_main_main_self_t* self = (_dualmodelreactor_main_main_self_t*)lf_new_reactor(sizeof(_dualmodelreactor_main_main_self_t));

    return self;
}
