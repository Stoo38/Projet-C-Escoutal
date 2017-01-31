#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Variable : public Bloc
{
	protected:

	public:
	Variable(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "variable", nLine, msgBox)
	{	
	}

	virtual void createTree() {};
	virtual void reorganizeLexemes() {};
	virtual void verifySyntax();
};
#endif
