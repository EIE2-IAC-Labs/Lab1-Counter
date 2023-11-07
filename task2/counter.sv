module counter #(
    parameter WIDTH = 8  // num of bits
)(
    // interface signals
    input  logic             clk,        // clock
    input  logic             rst,        // restart
    input  logic             en,         // counter enable
    output logic [WIDTH-1:0] count       // count output
);

/* // count up only
always_ff @ (posedge clk) 
    if (rst) count <= {WIDTH{1'b0}};
    else     count <= count + {{WIDTH-1{1'b0}}, en}; */

// count up or down
always_ff @ (posedge clk) 
    if (rst) count <= {WIDTH{1'b0}};
    else if (en) count <= count + {{WIDTH-1{1'b0}}, en};
    else count <= count + {WIDTH{1'b1}};

endmodule
