
module Achraf_Lab1 (
	clk_clk,
	reset_reset_n,
	pio_0_external_connection_export,
	pio_1_external_connection_export,
	pio_2_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input		pio_0_external_connection_export;
	output	[3:0]	pio_1_external_connection_export;
	output	[7:0]	pio_2_external_connection_export;
endmodule
