#ifndef _LEXEME_H_
#define _LEXEME_H_

#include <iostream>
#include <cstdlib>

using namespace std;

class Lexeme
{
   	public:
	string m_word;
	int m_line;
	string m_label;

	Lexeme(string word = "", int line = 0, string label = ""):
	m_word(word),
	m_line(line),
	m_label(label)
	{

	}	
};
#endif
