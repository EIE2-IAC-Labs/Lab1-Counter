#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char ** env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top veerylog instance
    Vtop* top = new Vtop;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open("top.vcd");
    
    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    top->bcd = 0;
    top->v = 0;



    //run simulation for many clock cycles
    for (i=0; i<3000; i++){

        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);        //unit is in ps!!!
            top->clk = !top->clk;
            top->eval();
        }

        top->rst = (i<2); // | (i == 15);
        top->en = (i>4);

        if (Verilated::gotFinish())  exit(0);  
    }
    tfp->close();
    exit(0);
}