#include "../HEADER/Library.h"

using namespace std;

void browseLexeme() const
{
	list<string>::iterator itr;
	int nbLexeme = 0;
	for (itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		switch(nbLexeme)
		{
			case 0:
				if (*itr == "library")
				{
					nbLexeme = 1;
				}
				else
				{
					itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter 
				}
				break;

			case 1:
				nbLexeme = 2;
				break;

			case 2:
				if (*itr == ";")
				{
					nbLexeme = 3;
				}
				else
				{
					itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter 
				}
				break;

			case 3:
				if (*itr == "use")
				{
					nbLexeme = 4;
					 
				}
				else
				{
					itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter
				}
				break;

			case 4:
				if (*itr == "library")
				{
					nbLexeme = 5;
				}
				else
				{
					itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter
				}
				break;

			case 5:
				if (*itr == ".")
				{
					nbLexeme = 6;
				}
				else
				{
					itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter
				}
				break;


//A REPRENDRE 
			case 6:
				if (*itr == "all")
				{
					itr = m_listLexemes.end();
				}
				else if ((*itr).m_word == m_identifiant.m_word)
				{	
					nbLexeme = 6;
				}
				else
				{
					itr = m_listLexemes.end();
					//Erreur à réfléchir et implémenter
				}
				break;


		}
	}
}
