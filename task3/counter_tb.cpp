#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char ** env){
    int i; //count the number of clock cycles to simulate
    int clk; //the module signal

    Verilated::commandArgs(argc, argv);
    // init top veerylog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open("counter.vcd");
    
    //init Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->ld = 0;

    //run simulation for many clock cycles
    for (i=0; i<3000; i++){              //in for loop the simulation happens

        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);        //unit is in ps!!!
            top->clk = !top->clk;
            top->eval();
        }

        // ++++ Send count value to Vbuddy as curve
        // vbdPlot(int(top->count), 0, 255);

        // ++++ Send count value to Vbuddy as HEX
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i+1);

        // ---- end of Vbuddy output section

        // change input stimuli
        vbdSetMode(1);                  //Set to One-Shot behaviour       
        top->rst = (i<2) | (i == 15);   //change reset in simulation
        top->ld = vbdFlag();
        if (Verilated::gotFinish())  exit(0);  
    }
    vbdClose();     // ++++
    tfp->close();
    exit(0);
}