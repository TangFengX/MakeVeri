#ifndef __SIM_CONFIG__
#define __SIM_CONFIG__
#include "sim_main.h"
#include "verilated.h"

#define ENABLE_LIMIT_TIME_STIMULATION 1
#define MAX_TIME_SIM 20
#define HALF_CLK_CYCLE 5
#define ENABLE_CLK_INPUT 1
#define CLK_PIN_NAME clock
#define ENABLE_INITIAL_BLOCK 1
#define INITIAL_BLOCK_MAX_STIMULATE_TIME 20
#define ENABLE_FOREVER_BLOCK 0
#define FOREVER_BLOCK_CYCLE 2

#define VERILATOR_MAIN_INITIAL_BLOCK()                                   \
    do                                                                   \
    {                                                                    \
            if (!ENABLE_INITIAL_BLOCK) \
                break; \
            VERILATOR_SWITCH_INPUT_TO(io_a, 0); \
            VERILATOR_SWITCH_INPUT_TO(io_b, 0); \
            VERILATOR_SWITCH_INPUT_TO(reset, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(10); \
            VERILATOR_SWITCH_INPUT_TO(reset, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(11); \
            VERILATOR_SWITCH_INPUT_TO(io_a, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(12); \
            VERILATOR_SWITCH_INPUT_TO(io_b, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(13); \
            VERILATOR_SWITCH_INPUT_TO(io_a, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(INITIAL_BLOCK_MAX_STIMULATE_TIME); \
    } while (0)

#define VERILATOR_MAIN_FOREVER_BLOCK()                               \
    vluint64_t T_start;                                              \
    do                                                               \
    {                                                                \
        T_start = T;                                                 \
            if (!ENABLE_FOREVER_BLOCK) \
                break; \
            VERILATOR_STEP_AND_EVAL_UNTIL(FOREVER_BLOCK_CYCLE + T_start); \
    } while (1)

#endif //__SIM_CONFIG__
