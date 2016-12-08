#include "../HEADER/Bloc.h"

using namespace std;

//ACCESSEURS
const string & Bloc::getIdentifiant() const
{
	return m_identifiant;
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
	
}


