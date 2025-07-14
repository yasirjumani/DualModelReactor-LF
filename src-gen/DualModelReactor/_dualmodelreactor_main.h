#ifndef _DUALMODELREACTOR_MAIN_H
#define _DUALMODELREACTOR_MAIN_H
#include "include/core/reactor.h"
#include "_scraphandler.h"
#include "_logger.h"
#include "_digitaltwinmonitor.h"
#include "_smartpredictor.h"










typedef struct {
    struct self_base_t base;
#line 21 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.h"
    #line 104 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    int wafer_id;
    #line 105 "/workspace/playground-lingua-franca/src/DualModelReactor.lf"
    bool busy;
#line 26 "/workspace/playground-lingua-franca/src-gen/DualModelReactor/_dualmodelreactor_main.h"
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_neg1;
    int _lf_neg1_width;
    struct {
        _digitaltwinmonitor_wafer_t wafer;
        _digitaltwinmonitor_p_neg1_t p_neg1;
        _digitaltwinmonitor_p1_t p1;
        _digitaltwinmonitor_p2_t p2;
        _digitaltwinmonitor_p4_t p4;
        _digitaltwinmonitor_p6_t p6;
        _digitaltwinmonitor_p7_t p7;
        _digitaltwinmonitor_p_neg2_t p_neg2;
    } _lf_mon;
    int _lf_mon_width;
    struct {
        _logger_wafer_t wafer;
        _logger_p_neg1_t p_neg1;
        _logger_p1_t p1;
        _logger_p2_t p2;
        _logger_p4_t p4;
        _logger_p6_t p6;
        _logger_p7_t p7;
        _logger_p_neg2_t p_neg2;
    } _lf_log;
    int _lf_log_width;
    struct {
        _scraphandler_wafer_t wafer;
        _scraphandler_p_neg1_t p_neg1;
        _scraphandler_p1_t p1;
        _scraphandler_p2_t p2;
        _scraphandler_p4_t p4;
        _scraphandler_p6_t p6;
        _scraphandler_p7_t p7;
        _scraphandler_p_neg2_t p_neg2;
    } _lf_scrap;
    int _lf_scrap_width;
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_p1;
    int _lf_p1_width;
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_p2;
    int _lf_p2_width;
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_p4;
    int _lf_p4_width;
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_p6;
    int _lf_p6_width;
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_p7;
    int _lf_p7_width;
    struct {
        _smartpredictor_wafer_id_t wafer_id;
        _smartpredictor_prediction_t* prediction;
        trigger_t prediction_trigger;
        reaction_t* prediction_reactions[1];
    } _lf_neg2;
    int _lf_neg2_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    reaction_t _lf__reaction_2;
    reaction_t _lf__reaction_3;
    reaction_t _lf__reaction_4;
    reaction_t _lf__reaction_5;
    reaction_t _lf__reaction_6;
    reaction_t _lf__reaction_7;
    trigger_t _lf__tick;
    reaction_t* _lf__tick_reactions[1];
} _dualmodelreactor_main_main_self_t;
_dualmodelreactor_main_main_self_t* new__dualmodelreactor_main();
#endif // _DUALMODELREACTOR_MAIN_H
