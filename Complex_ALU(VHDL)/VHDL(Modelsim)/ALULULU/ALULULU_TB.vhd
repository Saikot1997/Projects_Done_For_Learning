library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity ALULULU_TB is
    
end entity;

architecture CTB of ALULULU_TB is
    component ALULULU
    port (A : in std_logic_vector(3 downto 0);
          B : in std_logic_vector(3 downto 0);
	  SEL : in std_logic_vector(3 downto 0);
          Y : out std_logic_vector(3 downto 0);
	  MUL : out std_logic_vector(7 downto 0);
	  Re : Out std_logic_vector(3 downto 0));
    end component;

    signal A_TB : std_logic_vector(3 downto 0);
    signal B_TB: std_logic_vector(3 downto 0);
    signal SEL_TB : std_logic_vector(3 downto 0);
    signal Y_TB : std_logic_vector (3 downto 0);
    signal MUL_TB : std_logic_vector (7 downto 0);
    signal Re_TB : std_logic_vector (3 downto 0);

 begin


      DUT1: ALULULU port map (A => A_TB , B => B_TB , SEL => SEL_TB, Y => Y_TB, MUL => MUL_TB, Re => Re_TB);




	A_TB <= "0000", "0010" after 100ns, "0100" after 200ns,  "0110" after 300ns,   "0011" after 400ns, 
             "0011" after 500ns, "0011" after 600ns,  "0011" after 700ns,  "1010" after 800ns,   "1010" after 900ns,
	     "1010" after 1000ns, "1010" after 1100ns, "1010" after 1200ns;

	B_TB<= "0000", "0001" after 100ns, "0010" after 200ns,  "0011" after 300ns,   "0100" after 400ns, 
             "0101" after 500ns, "0110" after 600ns,  "0111" after 700ns,  "1000" after 800ns,   "1001" after 900ns,
	     "1010" after 1000ns, "1011" after 1100ns, "0110" after 1200ns;

	SEL_TB<= "0000", "0001" after 100ns, "1000" after 200ns,  "0011" after 300ns,   "0100" after 400ns, 
             "0001" after 500ns, "0011" after 600ns,  "0010" after 700ns,  "0111" after 800ns,   "0010" after 900ns,
	     "0011" after 1000ns, "0000" after 1100ns, "0001" after 1200ns;




end CTB;

