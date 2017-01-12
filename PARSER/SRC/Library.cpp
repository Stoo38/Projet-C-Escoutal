#include "../HEADER/Library.h"

using namespace std;

void Library::browseLexeme() 
{
	list<Lexeme>::iterator itr;
	int nbLexeme = 0;
 	int count = 0;
	for (itr == m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		switch(nbLexeme)
		{
			case 0:
				if ((*itr).m_word != "library")
				{
					
				}
				nbLexeme = 1;

					//itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter 
					//REFLECHIS PAS TROP TROP NON PLUS C EST DANGEREUX

				break;

			case 1:
				nbLexeme = 2;
				break;

			case 2:
				if ((*itr).m_word != ";")
				{
					
				}
				nbLexeme = 3;

					////itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter  
					//REFLECHIS PAS TROP TROP NON PLUS C EST DANGEREUX
				break;

			case 3:
				if ((*itr).m_word != "use")
				{
					
					 
				}

				nbLexeme = 4;

					//itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter 
					//REFLECHIS PAS TROP TROP NON PLUS C EST DANGEREUX
				
				break;

			case 4:
				if ((*itr).m_word != m_identifiant.m_word)
				{
					
				}

				nbLexeme = 5;

					//itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter 
					//REFLECHIS PAS TROP TROP NON PLUS C EST DANGEREUX

				break;

			case 5:
				if ((*itr).m_word != ".")
				{
					
				}

				nbLexeme = 6;
				

					//itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter 
					//REFLECHIS PAS TROP TROP NON PLUS C EST DANGEREUX

				break;


//A REPRENDRE ------> AIE AIE AIE
			case 6:
				if ((*itr).m_word != "all")
				{
					verifyLabel(*itr);

				}

				break;

			case 7:
				if ((*itr).m_word != ";")
				{
					//itr = m_listLexemes.end();
				}

				nbLexeme = 6;
				

				break;
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
