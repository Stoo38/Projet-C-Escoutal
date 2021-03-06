#ifndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <cstdlib>
#include <list>
#include "Lexeme.h"
#include "BlocNode.h"

using namespace std;
//Classe pour decouper les connexions en des elements les plus simples possibles
class Gate : public BlocNode
{
   	public:
	//string m_signal_a;
	//string m_signal_b;
	//string m_gate;

	Gate(const int nLine, Display &msgBox):
	BlocNode("default", "gate", nLine, msgBox)
	{

	}

	virtual	void verifySyntax();
	virtual void reorganizeLexemes();

};
#endif
