#include "../HEADER/Library.h"

using namespace std;

void Library::browseLexeme() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		cout << nbLexeme << endl;
		if (nbLexeme == 0)
		{
			if (monword == "library")
			{
				cout << "OKOKOKOKOKn°0" << endl;
				nbLexeme = 1;				
			}
			else
			{
				cout << "NONONOn°0" << endl;
				nbLexeme = 2;
			}
						
		}
		else if (nbLexeme == 1)
		{
			if (monword == "ieee")
			{
				cout << "OKOKOKOKOKn°1" << endl;
				nbLexeme = 2;
			}
			else
			{
				cout << "NONONOn°1" << endl;
			}
			nbLexeme = 2;			
		}
		else if (nbLexeme == 2)
		{
			if (monword == "library")
			{
				cout << "OKOKOKOKOKn°2" << endl;
				nbLexeme = 2;
			}
			else
			{
				cout << "NONONOn°2" << endl;
			}
			nbLexeme = 2;			
		}	 
	}
}


string Library::checkNextWord(int count, list<Lexeme>::iterator itr)
{
	if (count == (m_listLexemes.size()-1))
	{	
		cout << "Il n'y a plus de lexemes à verifier" << endl;
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
