
module Achraf_Lab1 (
	clk_clk,
	pio_0_external_connection_export,
	pio_1_external_connection_export,
	pio_2_external_connection_export,
	reset_reset_n);	

	input		clk_clk;
	input		pio_0_external_connection_export;
	input	[3:0]	pio_1_external_connection_export;
	output	[7:0]	pio_2_external_connection_export;
	input		reset_reset_n;
endmodule
