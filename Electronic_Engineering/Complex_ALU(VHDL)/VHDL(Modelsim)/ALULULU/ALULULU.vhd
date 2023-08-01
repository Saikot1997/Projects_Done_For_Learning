
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;
use IEEE.STD_LOGIC_arith.ALL;


entity ALULULU is                                           ---- entity declaration
    Port ( A 		: in  STD_LOGIC_VECTOR (3 downto 0);   ---- First Number Input
           B		: in  STD_LOGIC_VECTOR (3 downto 0);     ------- 2nd number input
           Y 		: out  STD_LOGIC_VECTOR (3 downto 0);   --- Output for all operation except multiplication
	   MUL 		: out  STD_LOGIC_VECTOR (7 downto 0);   ---- output for multiplication
           Re 		: out  STD_LOGIC_VECTOR (3 downto 0);   --- Reminder after division operation
           SEL 		: in  STD_LOGIC_VECTOR (3 downto 0));   ---- selection input to do specific operation
end ALULULU;

architecture Behavioral of ALULULU is

begin
ALULULU_Proc : Process(A,B,SEL)
	variable ac : STD_LOGIC_VECTOR(7 downto 0);    --- variable declation for division operation
	variable Mbar : STD_LOGIC_VECTOR(3 downto 0);   ---- variable declation for Division operation
	variable pv,bp : STD_LOGIC_VECTOR(7 downto 0);  ---- variable declation for Multiplication operation
Begin
Case SEL is
When "0000" =>               
	Y <= A and B;
When "0001" =>
	Y <= A or B;
When "0010" =>
	Y <= A nand B;
When "0011" =>
	Y <= A nor B;
When "0100" =>
	Y <= A xor B;
When "0101" =>
	Y <= A xnor B;
When "0110" =>
	Y <= not A;

When "0111" =>	            ------ Multiplication

		pv :="00000000";
		bp := "0000" & B;
	for i in 0 to 3 loop
	if a(i) = '1' then
		pv := pv + bp;
	end if;
		bp :=  bp(6 downto 0) & '0';
	end loop;
		MUL <= pv;
When "1000" =>		    ------ Division
	Mbar := not B;
	ac := "0000" & A;
	for i in 1 to 4 loop
	ac(7 downto 0) := ac(6 downto 0) & '0';
	ac(7 downto 4) := ac(7 downto 4) + Mbar + "0001" ;
	if ac(7) = '1' then
	ac(0) := '0' ;
	ac( 7 downto 4) := ac(7 downto 4) + B;
	else
		ac(0) := '1';
	end if;
	end loop;
	Y <= ac(3 downto 0);
	Re <= ac(7 downto 4);
	
When "1001" =>	           ----- Addition

             Y <= (A + B);
	
When "1010" =>	           ----- Substraction
	     Y <= (A - B);
when others => 
	NULL;
end case;
end process;
end Behavioral;

