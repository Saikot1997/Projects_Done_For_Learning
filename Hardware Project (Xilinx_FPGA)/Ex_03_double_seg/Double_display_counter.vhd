library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;



entity up_counter is
  Port (
           RST : in std_logic  ;
           clk :in std_logic ;
           enable :in std_logic  ;
           AN : out std_logic_vector(7 downto 0);
           LED_out_1 :out std_logic_vector (7 downto 0) 
   );
end up_counter;

architecture Behavioral of up_counter is

signal clk_counter : integer range 0 to 2147483647 := 0;
signal temp : natural range 0 to 10 := 0;
signal flag : std_logic :='0';
signal busy : std_logic := '0' ;
signal flag_counter : integer range 0 to 2147483647 := 0;
signal tens_increment : natural range 0 to 10 := 0;
signal sel_seg :  natural range 0 to 10 := 0;
begin

	process(clk,RST,enable)
	begin 
		if (rising_edge(clk) and enable = '1')  then 
		   if (RST = '1' OR temp >= 10) then
		   temp <= 0;
		   tens_increment <= tens_increment + 1;
		    if (tens_increment >= 10) then
		        tens_increment <= 0;
		        end if;
		   end if ;
			
		   clk_counter <= clk_counter + 1; 
		   if (clk_counter >= 50000000 )  then
			                   
			  temp <= temp + 1;
			  clk_counter <= 0;
			 
			  
			end if; 
		end if; 
     end process;


multiplexer : process(clk)
	begin 
		if (rising_edge(clk) )  then 
		   		
		 flag_counter <= flag_counter + 1;
		   if (flag_counter = 25000) then ------ 25000 
		     flag <= NOT flag;
		     flag_counter <= 0;
		   end if; 
		end if;
		
     end process;
     
     
 switch_disp :  process(flag)
	begin 
		if (flag<= '1') then 
		AN <= "11111110";
		
		end if;
		if (flag <= '0') then
		AN <= "11111101";
		
		end if;
		busy<= NOT busy;
     end process;    

process(flag,temp,tens_increment )
begin

if ( flag <= '1') then
 sel_seg <= temp;
 end if;
 
 if ( flag <= '0') then
 sel_seg <= tens_increment;
 end if;
  
 case sel_seg  is  --        8 bits for display 
    when 0 => LED_out_1 <= "11000000"; -- "0"
    when 1 => LED_out_1 <= "11111001"; -- "1" 
    when 2 => LED_out_1 <= "10100100"; -- "2" 
    when 3 => LED_out_1 <= "10110000"; -- "3" 
    when 4 => LED_out_1 <= "10011001"; -- "4" 
    when 5 => LED_out_1 <= "10010010"; -- "5" 
    when 6 => LED_out_1 <= "10000010"; -- "6"
    when 7 => LED_out_1 <= "11111000"; -- "7" 
    when 8 => LED_out_1 <= "10000000"; -- "8"     
    when 9 => LED_out_1 <= "10010000"; -- "9"
    when others => 
    LED_out_1 <= "11000000";
end case;
 
end process;

end Behavioral;