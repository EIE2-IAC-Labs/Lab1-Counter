module counter #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             en,       // enable (need to change the ld back to en cuz top.sv expects an input signal en)
  // input  logic [WIDTH-1:0] v,        // value to preload
  output logic [WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk) 
    if (rst) count <= {WIDTH{1'b0}};
    else     count <= count + {{WIDTH-1{1'b0}}, en};

endmodule
