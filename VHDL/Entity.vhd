entity
ALU
is
port
(
A
,
B
:
in 
STD_LOGIC_VECTOR
(
7
downto
0
)
; 
CMD		: in STD_LOGIC_VECTOR(2 downto 0) ;
Zero		: out std_logic;
S		: out STD_LOGIC_VECTOR(7 downto 0) ;
reset, clock	: in std_logic) ;

end ALU;