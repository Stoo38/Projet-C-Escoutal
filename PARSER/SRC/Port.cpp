#include "../HEADER/Port.h"

void Port::reorganizeLexemes()
{
	m_listLexemes.pop_front();
}

/*
{
string mytab[5];
mytab[0] = "std_logic";
mytab[1] = "bit";
mytab[2] = "std_logic_vector";
mytab[3] = "integer";
mytab[4] = "bit_vector";


for (int i = 0; i < 5; i++)
{
	if ((monmot == mytab[i]) && (i < 2))
	{
		//ici c'est les cas simple
		//...
		
		i = 5; //fin de boucle
	}
	if else (monmot == mytab[i])
	{
		//ici c'est les cas complexes
		//...
		
		i = 5; //fin de boucle
	}
}*/


