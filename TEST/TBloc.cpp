#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "../PARSER/HEADER/Bloc.h"
#include "../DISPLAY/Display.h"

using namespace std;

int main()
{
	Display Box(false); 
	int counterLine = 0;
	Bloc bloc1("ieee", "library", counterLine, Box);
	ifstream fichier("../VHDL/Library.vhd");
	if (fichier)
	{
		string mot;
		while(getline(fichier,mot))
		{
			bloc1.addLexeme(mot, counterLine);
			counterLine++;
		}
		bloc1.displayLexemes();
		Box.displayMessage();
	}
	else 
	{
		cout << "error" << endl;
	}
	
}
