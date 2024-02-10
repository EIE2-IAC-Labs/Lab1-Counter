#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // initialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation for many clock cycles
    for (i=0; i<300; i++) { // i is the cycle number
        
        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk);        // unit is in ps!!
            top->clk = !top->clk; // top->clk is the clock signal, for every i (cycle) the clock signal goes up and down
            top->eval ();
        }
        top->rst = (i <2) | (i == 23); // reset signal is high if cycle number is <2 or is cycle 23
        top->en = (i>4); // enable signal is high when i becomes >4
        if(i >= 14 && i < 17){ // the counter reaches 9 at cycle number 14, stopping for 3 cycles means stop until cycle 17
            top->en = 0;
        }
        if (Verilated::gotFinish())  exit(0); // once the counting has done (300 cycles has past) then the programme will terminate
    }
    tfp->close();
    exit(0);
}