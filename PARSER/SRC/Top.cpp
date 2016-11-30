#include "../HEADER/Top.h"

void Top::createBlocks()
{
	ifstream monFlux(m_vhdlFileName.c_str());

	if(monFlux)
	{
		string lexeme;
		string identifiant;
		do		
		{
			monFlux >> lexeme;
			lexeme = toMinuscule(lexeme);
			if (lexeme == "library")
			{							
				monFlux >> identifiant;
				identifiant = toMinuscule(identifiant);
				cout << "On entre dans un bloc " << lexeme << " dont l'identifiant est " << identifiant << endl;
			}
			else if (lexeme == "entity")
			{		
				monFlux >> identifiant;
				identifiant = toMinuscule(identifiant);
				cout << "On entre dans un bloc " << lexeme << " dont l'identifiant est " << identifiant << endl;
			}
			else
			{
				cout << lexeme << endl;
			}
				
		} while (monFlux.eof() != 1);	
		
	}
	else
	{
		cout << "ERROR: " << m_vhdlFileName << " not found" << endl;
	}
}

string Top::toMinuscule(string word)
{	
	for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (word[i] == j+65)
			{
				word[i] = j+97;
			}	
		}
	}
	
	return word;
}
