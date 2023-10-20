#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

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

    // init Vbuddy
    if (vbdOpen() != 1) return (-1);
    vbdHeader("Lab 1: Counter");    

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

        // ++++ Send count value to Vbuddy

        // using hex display
        // vbdHex(4, (int(top->count) >> 16) & 0xF);
        // vbdHex(3, (int(top->count) >> 8) & 0xF);
        // vbdHex(2, (int(top->count) >> 4) & 0xF);
        // vbdHex(1, int(top->count) & 0xF);

        // using plot display (plots a line increasing)
        vbdPlot(int(top->count), 0, 255); // 255 sets the max number that the graph can display/show on the TFT display, change it to another number to see the difference 
        
        vbdCycle(i+1);
        // ---- end of Vbuddy output section

        // change input stimuli
        // top->rst = (i <2) | (i == 15); // reset signal is high if cycle number is <2 or is cycle 15
        top->rst = i<2; // we need this line cuz if not rst is always 1
        // top->en = (i>4);
        top->en = vbdFlag(); // making the Flag the one that enables and disables counting
    
        if (Verilated::gotFinish())  exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}