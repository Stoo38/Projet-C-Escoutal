library IEEE ;
use IEEE.std_logic_1164.ALL ;

entity MachineEtat is
port (	clk 	: in std_logic ;
	resetn	: in std_logic ;
	P	: in std_logic ;
	F	: in std_logic ;
	M	: out std_logic;
	A	: out std_logic);	
end MachineEtat ;

architecture behaviour of MachineEtat is

type state_MachineEtat is (Idle, Count, Alarm) ;
signal current_state : state_MachineEtat ;
signal next_state : state_MachineEtat ;

begin
P_state : process (clk, resetn)

begin
	if (resetn = '0') then 
		current_state <= Idle;
	elsif (clk ='1' and clk'event) then 
		current_state <= next_state;
	end if; 
end process P_state ;

P_Next_State_output : process (current_state,P,F)
begin
	Case current_state is 
		when Idle => 	M <='0';
				A<='0';
 				if (P = '1') then next_state <=Count;
				else next_state <= Idle;	
				end if;

		when Count => 	M <='1';
				A<='0';
				if (F = '1') then next_state <= Alarm;
				elsif (P = '0' and F='0') then next_state <= Idle;
				else next_state <= Count;
				end if;

		when Alarm => 	M <='0';
				A<='1';
				if (P = '0') then next_state <= Idle;
				else next_state <= Alarm;
				end if;
	end case;
end process P_Next_State_output ;
end behaviour ;
