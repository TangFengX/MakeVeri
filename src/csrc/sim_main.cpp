#include "top_module_name.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include "sim_main.h"
#include "sim_config.h"
#include <nvboard.h>
#include <stdio.h>
#include <cstdlib>
#include <csignal>

void nvboard_bind_all_pins(Vtop *top);
VerilatedContext *contextp = new VerilatedContext;
Vtop *top = new Vtop(contextp);
VerilatedFstC *tfp = new VerilatedFstC;
vluint64_t T = 0;
vluint64_t clk = 0;

void close_wave()
{
    VERILATOR_FREE();
    printf("\n[Waveform] FST file has been closed successfully via atexit.\n");
}
void signal_handler(int sig) {
    if (sig == SIGINT) printf("\n[Signal] 捕捉到 Ctrl+C (SIGINT)\n");
    if (sig == SIGTSTP) printf("\n[Signal] 捕捉到 Ctrl+Z (SIGTSTP)\n");
    // 强制调用 exit(0)，这将自动触发 atexit 注册的 close_wave_assets
    std::exit(0); 
}
int main(int argc, char **argv)
{
    std::atexit(close_wave);
    std::signal(SIGINT, signal_handler);  
    std::signal(SIGTSTP, signal_handler);
    printf("Start\n");
    nvboard_bind_all_pins(top);
    nvboard_init();
    VERILATOR_INIT(argc, argv, true);
    VERILATOR_MAIN_INITIAL_BLOCK();
    VERILATOR_MAIN_FOREVER_BLOCK();
end:
    VERILATOR_FREE();
    return 0;
}
