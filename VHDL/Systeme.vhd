library IEEE ;
use IEEE_.std_logic_1164_.ALL ;
use ieee.numeric_std.all;
library lib_COMP ;
use lib_COMP.Compteur_;
use lib_COMP.MachineEtat;

entity Systeme is 
	port(	P_sys 	: in std_logic;
		clk_sys	: in std_logic;
		resetn_sys	: in std_logic;
		A_sys	: out std_logic);
end Systeme;

architecture behaviour of Systeme is

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
	
signal sig_P, sig_F, sig_M, sig_A	 : std_logic;
signal sig_clk, sig_rst_n		 : std_logic;

begin

sig_P<=P_sys;
sig_clk <= clk_sys;
sig_rst_n <= resetn_sys;

MachineEtat01 : MachineEtat port map (sig_clk,sig_rst_n,sig_P,sig_F,sig_M,sig_A);
Compteur01 : Compteur port map (sig_M,sig_clk,sig_rst_n,sig_P,sig_F);
 
A_sys<=sig_A;

end behaviour;

