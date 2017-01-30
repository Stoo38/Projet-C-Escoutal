#ifndef _PORT_H_
#define _PORT_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>
#include <stdio.h>
#include <stdlib.h>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Port : public Bloc
{
	protected:

	public:
	Port(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "port", nLine, msgBox)
	{	
	}

	virtual void reorganizeLexemes();
	virtual void verifySyntax();
};
#endif
