module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic              clk,
    input logic              rst,
    input logic              en,
    output logic [WIDTH-1:0] count
);

always_ff @( posedge clk ) 
    if(rst) count <= {WIDTH{1'b0}};
    else    count <= {{WIDTH-1{1'b0}}, en};

endmodule
