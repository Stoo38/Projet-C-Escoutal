#include "../HEADER/Bloc.h"

using namespace std;

//ACCESSEURS
const string & Bloc::getIdentifiant() const
{
	return m_identifiant.m_word;
}

//MODIFIEURS
void Bloc::addLexeme(string lexeme, int nLine)
{
	Lexeme newLexeme(lexeme, nLine);
	m_listLexemes.push_back(newLexeme);
}

void Bloc::displayLexemes()
{
	list <Lexeme>::iterator itr;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		cout << (*itr).m_line << " " << (*itr).m_word << endl;		 
	}
}





int Bloc::trySpecialCharacter(Lexeme lex)
{
	string word = lex.m_word;
	if(word.size() == 1)
	{
		for(char i = 33; i < 127; i++)
		{
			if(word[0] == i)
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
	}
	return 0;		
}

void Bloc::verifyFirstCharacter(Lexeme lex)
{
	string word = lex.m_word;
	int error = 1;
	if (trySpecialCharacter(lex) != 1)
	{
		for (char i = 97; i < 123; i++)
		{
			if(word[0] == i)
			{
				error = 0;
			}
		}
	}
	if (error == 1)
	{
		m_msgBox.createMessage("06", lex.m_line, lex.m_word);
	}
}

void Bloc::verifyUnderscore(Lexeme lex)
{
	
}

void Bloc::verifyGlobalWord(Lexeme lex)
{
	m_msgBox.createMessage("05", lex.m_line, lex.m_word);
}


