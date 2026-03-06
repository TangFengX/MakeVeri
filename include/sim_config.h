#ifndef __SIM_CONFIG__
#define __SIM_CONFIG__
#include "sim_main.h"
#include "verilated.h"

#define ENABLE_LIMIT_TIME_STIMULATION 1
#define MAX_TIME_SIM 220
#define HALF_CLK_CYCLE 1
#define ENABLE_CLK_INPUT 0
#define CLK_PIN_NAME clk
#define ENABLE_INITIAL_BLOCK 1
#define INITIAL_BLOCK_MAX_STIMULATE_TIME 220
#define ENABLE_FOREVER_BLOCK 0
#define FOREVER_BLOCK_CYCLE 4
#define ENABLE_WAVEFROM_ACQUISITION 1

#define VERILATOR_MAIN_INITIAL_BLOCK()                                   \
    do                                                                   \
    {                                                                    \
            if (!ENABLE_INITIAL_BLOCK) \
                break; \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_SWITCH_INPUT_TO(rst_n, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(1); \
            VERILATOR_SWITCH_INPUT_TO(rst_n, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(2); \
            VERILATOR_SWITCH_INPUT_TO(rst_n, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(10); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(12); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(14); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(16); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(18); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(20); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(22); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(24); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(26); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(28); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(30); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(32); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(34); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(36); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(38); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(40); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(42); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(44); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(46); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(48); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(50); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(52); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(54); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(56); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(58); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(60); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(62); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(64); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(66); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(68); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(70); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(72); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(74); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(85); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(87); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(89); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(91); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(93); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(95); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(97); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(99); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(101); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(103); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(105); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(107); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(109); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(111); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(113); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(115); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(117); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(119); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(121); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(123); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(125); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(127); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(129); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(131); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(133); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(135); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(137); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(139); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(141); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(143); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(145); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(147); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(149); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(160); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(162); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(164); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(166); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(168); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(170); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(172); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(174); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(176); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(178); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(180); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(182); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(184); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(186); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(188); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(190); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(192); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(194); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(196); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(198); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(200); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(202); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(204); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(206); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(208); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(210); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(211); \
            VERILATOR_SWITCH_INPUT_TO(ps2_dat, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(212); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(214); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
            VERILATOR_STEP_AND_EVAL_UNTIL(216); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 0); \
            VERILATOR_STEP_AND_EVAL_UNTIL(218); \
            VERILATOR_SWITCH_INPUT_TO(ps2_clk, 1); \
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
