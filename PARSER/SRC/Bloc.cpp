#include "../HEADER/Bloc.h"

using namespace std;

//ACCESSEURS
const string & Bloc::getIdentifiant() const
{
	return m_identifiant.m_word;
}

const string Bloc::getNameBlock() const
{
	return (m_listLexemes.front()).m_word;
}

//MODIFIEURS
void Bloc::addLexeme(string lexeme, int nLine)
{
	Lexeme newLexeme(lexeme, nLine);
	m_listLexemes.push_back(newLexeme);
}

void Bloc::displayLexemes()
{
	cout << "List of lexemes contained in the block " << getNameBlock() << " " << getIdentifiant() << endl;
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
	string word = lex.m_word;
	if ((word[word.size()-1] == 95) || (word[0] == 95)) 
	{
		m_msgBox.createMessage("07", lex.m_line, lex.m_word);
	}
}

void Bloc::verifyGlobalWord(Lexeme lex)
{
	string word = lex.m_word;
	for (int i = 0; i < word.size(); i++)
	{
		int error = 1;
		for (char j = 48; j < 123; j++)
		{
			if(word[i] == j)
			{
				error = 0;
				j = 123;
			}
			if (j == 57)
			{
				j = 94;
			}
			if (j == 95)
			{
				j++;
			}
		}
		if (error == 1)
		{
			m_msgBox.createMessage("08", lex.m_line, lex.m_word);
		}
	}
}

void Bloc::verifyLabel(Lexeme lex)
{
	verifyGlobalWord(lex);
	verifyUnderscore(lex);
	verifyFirstCharacter(lex);
	compareKeyWords(lex);
}

void Bloc::compareKeyWords(Lexeme lex)
{
	/*ifstream myFile("PARSER/keywords.txt");  	

	if(myFile)					
	{		
		string line;				
		while(getline(myFile, line))					
		{
			if (lex.m_word == line)
			{
				m_msgBox.createMessage("26", lex.m_line, lex.m_word);
			}
		}					
	}
	else
	{
		m_msgBox.createMessage("25", 0, "keywords.txt");		
	}*/	
}

string Bloc::checkNextWord(int count, list<Lexeme>::iterator itr)
{
	if (count == (m_listLexemes.size()-1))
	{	
		return "";		
	}
	
	else 
	{
		list<Lexeme>::iterator itr2;
		itr2 = itr;
		itr2++;

		return (*itr2).m_word;
	}
}

