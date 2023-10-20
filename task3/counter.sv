module counter #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             ld,       // load signal (load counter from data: when ld is asserted, the value v is loaded into the counter as a pre-set value)
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [WIDTH-1:0] count     // count output
);

/* // step 1: loadable counter
always_ff @ (posedge clk)
  if (rst) count <= {WIDTH{1'b0}};
  else     count <= ld ? v : count + {{WIDTH-1{1'b0}},1'b1};
                // if ld is 1 then count will be v (LHS of the :), if ld is 0 then count will be whatever's on the RHS of the :
 */

// step 2: single stepping
always_ff @ (posedge clk)
  if (rst) count <= {WIDTH{1'b0}};
  else if (ld)  count <= count + {{WIDTH-1{1'b0}},1'b1};
                // if ld is 1 then count will be v (LHS of the :), if ld is 0 then count will be whatever's on the RHS of the :

endmodule
