#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "../PARSER/HEADER/Bloc.h"
#include "../DISPLAY/Display.h"
#include "../PARSER/HEADER/Lexeme.h"

using namespace std;

int main()
{
	Display Box(false); 
	int counterLine = 0;
	Bloc bloc1("ieee", "library", counterLine, Box);
	ifstream fichier("/home/phelma/Projet-C-Escoutal/VHDL/Library.vhd");
	if (fichier)
	{
		string mot;
		while(getline(fichier,mot))
		{
			bloc1.addLexeme(mot, counterLine);
			counterLine++;
		}
		bloc1.displayLexemes();

		Lexeme lexlex("b;", 0);
	 	bloc1.verifyLabel(lexlex);
		Lexeme lexlex2("_es)sai", 0);
	 	bloc1.verifyLabel(lexlex2);
		Lexeme lexlex3("_essai_;;;", 0);
	 	bloc1.verifyLabel(lexlex3);
		Box.displayMessage(true);
	}
	else 
	{
		cout << "errror" << endl;
	}
	
}
