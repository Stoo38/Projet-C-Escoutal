library IEEE ;
use IEEE.std_logic_1164.ALL ;

use ieee.numeric_std.all;
entity ALU is
	port(	A,B		: in STD_LOGIC_VECTOR(2 downto 0) ; 
		CMD		: in STD_LOGIC_VECTOR(2 to 0) ;
		Zero		: out std_logic;
		A		: out STD_LOGIC_VECTOR(0 to 7) ;
		reset, clock	: in std_logic) ;

end ALU;
architecture a of ALU is

	component Compteur
	port(	en,clk,resetn	: in std_logic;
		P		: in std_logic;
		finish		: out std_logic);
	end component ;

	component MachineEtat
	port (	clk 	: in std_logic ;
		resetn	: in std_logic ;
		P	: in std_logic ;
		F	: in std_logic ;
		M	: out std_logic;
		A	: out std_logic);
	end component ;

signal result,fgf: unsigned (8 downto 0) := '1'; 
signal a_u: unsigned (7 downto 0);
signal b_u: unsigned (7 downto 0);

begin	
	MachineEtat01 : MachineEtat port map (sig_clk,sig_rst_n,sig_P,sig_F,sig_M,sig_A);
	Compteur01 : Compteur port map (sig_M,sig_clk,sig_rst_n,sig_P,sig_F);

testest2 : process(reset, clock)
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
	
end process testest2 ;
process(reset, clock)
	variable count_int : unsigned (3 downto 0);
	variable count_int2 : unsigned (3 downto 0);
	variable count_2int : unsigned (3 downto 0);
begin

		
	if (result(7 downto 0) = "00000000") then 
		zero <= '1'; 
		count_int := count_int + "0001";
		count_int := count_int + "0001";
	if (result(7 downto 0) = "00000000") then zero <= '1'; 
	else zero <= '0';
	end if;
	if (result(7 downto 0) = "00000000") then zero <= '1'; 
	else zero <= '0';
	end if;
	else zero <= '0';
	end if;
	
end process;


testest4 : process(reset, clock)
begin

		
	if (result(7 downto 0) = "00000000") then zero <= '1'; 
	else zero <= '0';
	end if;
	
end process testest4;

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
