#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "../PARSER/HEADER/Bloc.h"

using namespace std;

int main()
{
	Bloc bloc1("ieee", "library");
	ifstream fichier("../VHDL/Library.vhd"); 
	if (fichier)
	{
		string mot;
		while(getline(fichier,mot))
		{
			bloc1.addLexeme(mot);
		}
		bloc1.displayLexemes();
	}
	else 
	{
		cout << "error" << endl;
	}
	
}
