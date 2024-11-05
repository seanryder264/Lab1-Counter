// Mandatory header files. Note the name Vcounter.h for the module counter
#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    // i counts the number of clock cycles to simulate. clk is the module clock signal
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    // Instantiate the counter module as Vcounter, which is the name of all generated files. This is the DUT!
    Vcounter* top = new Vcounter;
    //init trace dump
    // Turn on signal tracing, and tell Verilator to dump the waveform data to counter.vcd
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    //initialize simulation inputs
    //Set inital signals levels. Top is the name of the top-level entity. Only the top-level signals are visible.
    top->clk = 1;
    top->rst = 1;
    top-> en = 0;

    // run simulation for many clock cycles
    // This is the for-loop where simulation happend. i counts the clock cycles
    for (i=0; i<300; i++) {
        
        //dump variables into VCD file and toggle clock
        // This is the for-loop that toggles the clock. It also ouput the trace for each half of the clock cycle, and force the model to evaluate on both edges of the clock
        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval();
        }
        // Change rst and en signals during simulation
        top->rst = (i<2);
        top->en = (i>4);
        if (top->count == 0x9){
            top->en = 0;
            for (int wait_cycles=0; wait_cycles<3; wait_cycles++){
                for (clk=0; clk<2; clk++) {
                    tfp->dump (2*i+clk);
                    top->clk = !top->clk;
                    top->eval();
                }
            }
            top->en = 1;
        }
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}
