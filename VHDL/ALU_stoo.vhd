
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

 
end A;
