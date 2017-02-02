#ifndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <cstdlib>
#include <list>
#include "Lexeme.h"

using namespace std;
//Classe pour decouper les connexions en des elements les plus simples possibles
class Gate
{
   	public:
	list <Lexeme> m_listLexemes;
	//string m_signal_a;
	//string m_signal_b;
	//string m_gate;

	Gate()
	{

	}	

	void displayLexemes();
};
#endif
