library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;
entity ALU is
	port(	A,B		: in STD_LOGIC_VECTOR(7 downto 0) ; 
		CMD		: in STD_uLOGIC_VECTOR(2 downto 0) ;
		Zero		: out std_ulogic;
		S		: out STD_LOGIC_vector(7 downto 0) ;
		TEST		: in integer range 4 to 8;
		reset, clock	: in std_logic) ;

end ALU;

--architecture a of ALU is

--	component Compteur
--	port(	en,clk,resetn	: in std_logic;
--		P		: in std_logic;
--		finish		: out std_logic);
--	end component ;
--
--	component MachineEtat
--	port (	clk 	: in std_logic ;
--		resetn	: in std_logic ;
--		P	: in std_logic ;
--		F	: in std_logic ;
--		M	: out std_logic;
--		A	: out std_logic);
--	end component ;


