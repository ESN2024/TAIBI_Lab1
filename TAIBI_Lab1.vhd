Library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;


entity Lab1 is
	port (
	clk : in std_logic;
	reset : in std_logic;
	trigger_in : in std_logic;
	speed_in : in std_logic_vector(3 downto 0);
	leds_out : out std_logic_vector(7 downto 0)
	);
end entity Lab1;

architecture behav of Lab1 is
    component Achraf_Lab1 is
        port (
            clk_clk             : in  std_logic                    := 'X';             -- clk
            leds_export         : out std_logic_vector(7 downto 0);                    -- export
            reset_reset_n       : in  std_logic                    := 'X';             -- reset_n
            switch_speed_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
            trigger_export      : in  std_logic                    := 'X'              -- export
        );
    end component Achraf_Lab1;
	
	
	begin

	u0 : component Achraf_Lab1
        port map (
            clk_clk             => clk,             --          clk.clk
            leds_export         => leds_out,         --         leds.export
            reset_reset_n       => reset,       --        reset.reset_n
            switch_speed_export => speed_in, -- switch_speed.export
            trigger_export      => trigger_in       --      trigger.export
        );
			
end architecture behav;
