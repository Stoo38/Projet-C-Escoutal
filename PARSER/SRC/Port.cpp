#include "../HEADER/Port.h"

{
string monmot;
string mytab[5];
mytab[0] = "std_logic";
mytab[1] = "bit";
mytab[2] = "std_logic_vector";
mytab[3] = "integer";
mytab[4] = "int_vector";

bool flagMotTrouve = false;
for (int i = 0; i < 5; i++)
{
	if ((monmot == mytab[i]) && (i < 2))
	{
		//ici c'est les cas simple
		//...
		flagMotTrouve = true;
		i = 5; //fin de boucle
	}
	if else (monmot == mytab[i])
	{
		//ici c'est les cas complexes
		//...
		flagMotTrouve = true;
		i = 5; //fin de boucle
	}
}
if (flagMotTrouve == true)
{
	//Le mot a ete trouve dans la boucle
}
else
{
	//Le mot n'a pas ete trouve dans la boucle
}


