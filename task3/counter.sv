module counter #(
    parameter WIDTH = 8  // num of bits
)(
    // interface signals
    input  logic             clk,        // clock
    input  logic             rst,        // restart
    input  logic             en,         // counter enable
    output logic [WIDTH-1:0] count       // count output
);

/* // synchronous reset
always_ff @ (posedge clk) 
    if (rst) count <= {WIDTH{1'b0}};
    else     count <= count + {{WIDTH-1{1'b0}}, en}; */

/* // asynchronous reset
always_ff @ (posedge clk, posedge rst) // what this means is it will check for the +ve rising edge of both the clock signal and reset signal, so if reset signal is high reset will happen regardless of what the clock signal is
    if (rst) count <= {WIDTH{1'b0}};
    else     count <= count + {{WIDTH-1{1'b0}}, en}; */

// count up or down
always_ff @ (posedge clk) 
    if (rst) count <= {WIDTH{1'b0}};
    else if (en) count <= count + {{WIDTH-1{1'b0}}, en};
    else count <= count + {WIDTH{1'b1}};

endmodule
