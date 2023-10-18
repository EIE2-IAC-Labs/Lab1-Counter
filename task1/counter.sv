module counter #(
    parameter WIDTH = 8  // num of bits
)(
    // interface signals
    input  logic             clk,        // clock
    input  logic             rst,        // restart
    input  logic             en,         // counter enable
    output logic [WIDTH-1:0] counter     // count output
);

always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}};
    else     count <= count + {{WIDTH-1{1'b0}}, en};

endmodule