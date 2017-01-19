#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>

#include "../PARSER/HEADER/Library.h"		
#include "../DISPLAY/Display.h"

using namespace std;

int main()
{
	Display Box(false); 	
	Library mylib("ieee", 1, Box);
	int counterLine = 0;

	ifstream fichier("/users/phelma/phelma2015/mahtalb/Projet-C-Escoutal/VHDL/Library.vhd");
	if (fichier)
	{
		string mot;
		while(getline(fichier,mot))
		{
			mylib.addLexeme(mot, counterLine);
			counterLine++;
		}
		mylib.displayLexemes();

		mylib.browseLexeme();
		//Box.displayMessage();
	}

	else 
	{
		cout << "Fichier non ouvert" << endl; 
	}
}

