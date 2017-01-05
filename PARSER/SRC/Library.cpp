#include "../HEADER/Library.h"

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
					nbLexeme++;
				}
				else
				{
					itr = m_listLexemes.end();
				}
				break;

			case 1:
				if ()
				{
					nbLexeme++;
				}
				else
				{
				
				}
				break;
		}
	}
}
