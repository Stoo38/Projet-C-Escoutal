#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "PARSER/HEADER/Top.h"

using namespace std;

int main(int argc, char *argv[])
{
	string function(argv[1]);
	string file(argv[2]);
	if (function == "tree")
	{
		Top myTop(file);
		myTop.createTree();		
	}
	else
	{
		cout << "Premier parametre incorrect: le choix de la fonction n'est pas valide" << endl;
	}


	
}
