#ifndef _CONNEXION_H_
#define _CONNEXION_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocInstruction.h"
#include "Gate.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Connexion : public BlocInstruction
{
	protected:
	Gate m_gate;

	public:
	Connexion(const int nLine, Display &msgBox):
	BlocInstruction("default", "connexion", nLine, msgBox)
	{	
	}
	
	virtual void createTree();
	virtual void reorganizeLexemes();
};
#endif
