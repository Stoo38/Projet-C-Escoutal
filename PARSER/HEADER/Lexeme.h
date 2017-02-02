#ifndef _LEXEME_H_
#define _LEXEME_H_

#include <iostream>
#include <cstdlib>

using namespace std;
//Classe pour stocker chaque lexeme et y associer d'eventuels attributs
class Lexeme
{
   	public:
	string m_word;		//Contient le lexeme
	int m_line;		//Contient la ligne

	Lexeme(string word = "", int line = 0):
	m_word(word),
	m_line(line)
	{

	}	
};
#endif
