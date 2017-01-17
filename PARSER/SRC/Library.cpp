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
				
			}
						
		}
		else if (nbLexeme == 1)
		{
			cout << "OKOKOKOKOKn°1" << endl;
			nbLexeme = 2;
		
		}
		else if (nbLexeme == 2)
		{
			if (monword == ";")
			{
				cout << "OKOKOKOKOKn°2" << endl;
				cout << "Next word: " << checkNextWord(nbLexeme, itr) << endl;

				nbLexeme = 3;
			}
			else
			{
				cout << "NONONOn°2" << endl;
			}
		
		}	

		else if (nbLexeme == 3)
		{
			if (monword == "use")
			{
				cout << "OKOKOKOKOKn°3" << endl;
				nbLexeme = 4;
			}
			else
			{
				cout << "NONONOn°3" << endl;
			}
		
		}	
	
		else if (nbLexeme == 4)
		{
			if (monword == m_identifiant.m_word)
			{
				cout << "OKOKOKOKOKn°4" << endl;
				cout << "Next word: " << checkNextWord(nbLexeme, itr) << endl;
				nbLexeme = 5;
			}
			else
			{
				cout << "NONONOn°4" << endl;
			}
		
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
