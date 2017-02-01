library STD; --manque y
  use STD.textio.all; --manque .
library IEEE; --pas d'espace
  use IEEE.bit_1164.all; --un espace en trop
  use IEEE.bit_misc.all ;--pas de ;
  use IEEE.bit_arith.all;

entity assign is --pas de is
  port   (--pas de (  
    CLK :       In    bt; --bt inconnu
    RST :       In   bit; --mauvais separateur
    start, :      In  bit; -- manque un port 
    done :      out  bit;
    DIN :       ni    bit_vector(15 downto 0); -- direction signal?
    DOUT :       Out   bit_vector(15   0) -- downto?
    );  -- manque )
  end signaux; -- incoherence dans le nom de l'entiy

architecture struct of  toto is  --mauvais nom d'entite

signal data_round_in       : bit_vector(15 downto 0);
signal data_round_out       : bit_vector(15 downto 0); -- signal
signal last_round_signal, first_round_signal    : bit;




end structe;  --nom archi


