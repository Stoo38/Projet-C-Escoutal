#include "../HEADER/Gate.h"

void Gate::displayLexemes()
{
	cout << "List of lexemes contained in the gate connexion " << endl;
	list <Lexeme>::iterator itr;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		cout << (*itr).m_line << " " << (*itr).m_word << endl;		 
	}
}
