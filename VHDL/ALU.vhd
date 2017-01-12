library IEEE ;
use IEEE.std_logic_1164.ALL ;

use ieee.numeric_std.all;
entity ALU is
	port(	A,B		: in STD_LOGIC_VECTOR(7 downto 0) ; 
		CMD		: in STD_LOGIC_VECTOR(2 downto 0) ;
		Zero		: out std_logic;
		S		: out STD_LOGIC_VECTOR(7 downto 0) ;
		reset, clock	: in std_logic) ;

end ALU;
architecture A of ALU is

signal result: unsigned (8 downto 0); 
signal a_u: unsigned (7 downto 0);
signal b_u: unsigned (7 downto 0);

begin	

process(reset, clock)
begin
	
	
	if (reset = '1') then 
	result <= "000000000";	
	a_u <= "00000000";
	b_u <= "00000000";
	S<= std_logic_vector(result(7 downto 0)); --define the value of S in function of result (8 bits)
	elsif clock'event and clock = '1' then
		a_u<= unsigned(a);
		b_u<= unsigned(b);
		case CMD is
			when("000") => result <= ('0' & a_u);
			when("001") => result <= ('0' & a_u) + ('0' & b_u );
			when("010") => result <= ('0' & a_u) - ('0' & b_u );
			when("011") => result <= ('0' & b_u) - ('0' & a_u );
			when("100") => result <= ('0' & a_u) XOR ('0' & b_u );
			when("101") => result <= ('0' & a_u) OR ('0' & b_u );		
			when("110") => result <= ('0' & a_u) AND ('0' & b_u );
			when("111") => result <= ('0' & a_u) + "000000001";
			when others => result <= "111111111";
		end case;
	S<= std_logic_vector(result(7 downto 0)); --define the value of S in function of result (8 bits)			
	end if;
		
	if (result(7 downto 0) = "00000000") then zero <= '1'; 
	else zero <= '0';
	end if;
	
end process;

--zero<= '1' when result(7 downto 0) = "00000000" else '0';
--S<= std_logic_vector(result(7 downto 0)); --define the value of S in function of result (8 bits)
--a_u<= unsigned(a);
--b_u<= unsigned(b);

-- choose the operation in function of CMD
--with CMD select result<= "000000000" when "000", 
			 --('0' & a_u) + ('0' & b_u ) when "011", -- a+b on 9 bits 			
   			 --('0' & a_u) - ('0' & b_u ) when "010", -- a-b on 9 bits
			 --('0' & b_u) - ('0' & a_u ) when "001", -- b-a on 9 bits 
			 --('0' & a_u) XOR ('0' & b_u ) when "100",
			 --('0' & a_u) AND ('0' & b_u ) when "110",
			 --('0' & a_u) OR ('0' & b_u ) when "101",
    			 --"111111111" when others; 
end A;
