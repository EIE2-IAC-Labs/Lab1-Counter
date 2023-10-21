// this task focus on displaying BCD numbers on the Vbuddy, ignore the pre-loading

#include "Vtop.h"  // change "Vcounter.h" to "Vtop.h" 
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vtop* top = new Vtop; // cuz now the instance of the device we're running is Vtop (top.sv) so need change from Vcounter to Vtop

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
    top->rst = 0;
    top->en = 1;

    // no need these two lines for now cuz these are for pre-loading
    // top->ld = 0;
    // top->v = vbdValue();

    // run simulation for many clock cycles
    for (i=0; i<300; i++) { // i is the cycle number
        
        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk);        // unit is in ps!!
            top->clk = !top->clk; 
            top->eval ();
        }

        // ++++ Send count value to Vbuddy

        // using hex display
        vbdHex(4, (int(top->bcd) >> 16) & 0xF);
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, int(top->bcd) & 0xF);
        
        vbdCycle(i+1);
        // ---- end of Vbuddy output section

        // no need these 3 lines cuz these are for pre-loading
        // vbdSetMode(1);
        // top->ld = vbdFlag();
        // top->v = vbdValue();
    
        if (Verilated::gotFinish())  exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}