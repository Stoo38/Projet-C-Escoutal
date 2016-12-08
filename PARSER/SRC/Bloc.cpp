#include "../HEADER/Bloc.h"

using namespace std;

//ACCESSEURS
const string & Bloc::getIdentifiant() const
{
	return m_identifiant;
}

const int & Bloc::getError() const
{
	return m_error;
}

//MODIFIEURS
void Bloc::addLexeme(string lexeme)
{
	m_listLexemes.push_back(lexeme);
}

void Bloc::displayLexemes()
{
	list <string>::iterator itr;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		cout << *itr << endl;		 
	}
}





int Bloc::trySpecialCharacter(string lexeme)
{
	if(lexeme.size() == 1)
	{
		for(char i = 33; i < 127; i++)
		{
			if(lexeme[0] == i)
			{
				return 1;
			}	
			if (i == 47)
			{
				i = 57;
			}
			if (i == 64)
			{
				i = 90;
			}
			if (i == 94)
			{
				i = 95;
			}
			if (i == 96)
			{
				i = 122;
			}
		}
		return 0;
	}
	else
	{
		return 0;
	}		
}

int Bloc::verifyFirstCharacter(string lexeme)
{
	int error = 1;
	if (trySpecialCharacter(lexeme) != 1)
	{
		for (char i = 97; i < 123; i++)
		{
			if(lexeme[0] == i)
			{
				error = 0;
			}
		}
	}
	return error;
}

int Bloc::verifyUnderscore(string lexeme)
{
	
}

int Bloc::verifyGlobalWord(string lexeme)
{
	return 0;
}


