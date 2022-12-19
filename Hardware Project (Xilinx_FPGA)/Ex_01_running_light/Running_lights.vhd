library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Running_lights is
    Port ( clk : in  STD_LOGIC;
           LED : out  bit_vector(15 downto 0)
           );
end Running_lights;

architecture Behavioral of Running_lights is
	signal clk_counter : integer range 0 to 2147483647 := 0;
	
signal light : natural range 0 to 15 := 0;
begin
	
	process(clk)
	begin 
		if (rising_edge(clk))  then 
			clk_counter <= clk_counter + 1; 
			if (clk_counter >= 25000000)  then 
			                   
			  light <= light + 1;
			  clk_counter <= 0;
			  
			  if light >= 15 then
			     light <= 0;
			   end if;
			  
			end if; 
		end if; 
end process;
	--LED <= "0000000000000000";
	process(clk,light)
	begin
	case light is
    when 0 =>
        LED <= "0000000000000001";
    when 1 =>
        LED <= "0000000000000010";
    when 2 =>
        LED <= "0000000000000100";
    when 3 =>
        LED <= "0000000000001000";
    when 4 =>
        LED <= "0000000000010000";
    when 5 =>
        LED <= "0000000000100000";
    when 6 =>
        LED <= "0000000001000000";
    when 7 =>
        LED <= "0000000010000000";
    when 8 =>
        LED <= "0000000100000000";
    when 9 =>
        LED <= "0000001000000000";
    when 10 =>
        LED <= "0000010000000000";
    when 11 =>
        LED <= "0000100000000000";
    when 12 =>
        LED <= "0001000000000000";
    when 13 =>
        LED <= "0010000000000000";
    when 14 =>
        LED <= "0100000000000000";
    when 15 =>
         LED <= "1000000000000000";
        
end case;
    end process;
	
end Behavioral;