#include "../HEADER/Library.h"

using namespace std;

void Library::browseLexeme() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		
		cout << count << " " << m_listLexemes.size() << endl;


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
				cout << "Next word: " << checkNextWord(count, itr) << endl;

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
				cout << "Next word: " << checkNextWord(count, itr) << endl;
				nbLexeme = 5;
			}
			else
			{
				cout << "NONONOn°4" << endl;
			}
		}	
	
		else if (nbLexeme == 5)
		{
			if (monword == ".")
			{
				if (checkNextWord(count, itr) == "all")
				{
					cout << "OKOKOKOKOKn°5" << endl;
					cout << "Next word: " << checkNextWord(count, itr) << endl;
					nbLexeme = 7;
				}
				else
				{
					cout << "OKOKOKOKOKn°5" << endl;
					cout << "Next word: " << checkNextWord(count, itr) << endl;
					nbLexeme = 6;
				}
			}
			else
			{
				cout << "NONONOn°5" << endl;
			}
		}	
	
		else if (nbLexeme == 6)
		{
			verifyLabel(*itr);
			if (checkNextWord(count, itr) == ".")
			{
				cout << "OKOKOKOKOKn°6" << endl;
				cout << "Next word: " << checkNextWord(count, itr) << endl;
				nbLexeme = 5;
			}
			else
			{
				cout << "OKOKOKOKOKn°6" << endl;
				cout << "Next word: " << checkNextWord(count, itr) << endl;
				nbLexeme = 8;
			}
		}

		else if (nbLexeme == 7)
		{
			if (monword == "all")
			{
				cout << "OKOKOKOKOKn°7" << endl;
				cout << "Next word: " << checkNextWord(count, itr) << endl;

				nbLexeme = 8;
			}
			else
			{
				cout << "NONONOn°7" << endl;
			}	
		}	

		else if (nbLexeme == 8)
		{
			if (monword == ";")
			{
				if (checkNextWord(count, itr) == "")
				{
					cout << "OKOKOKOKOKn°8" << endl << "Fin du game !" << endl;
				}
				else if (checkNextWord(count, itr) == "library")
				{
					cout << "OKOKOKOKOKn°8" << endl;
					cout << "Next word: " << checkNextWord(count, itr) << endl;
					nbLexeme = 0;
				}
				else if (checkNextWord(count, itr) == "use")
				{
					cout << "OKOKOKOKOKn°8" << endl;
					cout << "Next word: " << checkNextWord(count, itr) << endl;
					nbLexeme = 3;
				}
				else
				{
					cout << "NONONOn°8" << endl;
				}	

			}
			else
			{
				cout << "NONONOn°8" << endl;
			}	
		}
		count++;	
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
