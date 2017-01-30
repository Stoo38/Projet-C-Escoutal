#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Signal : public Bloc
{
	protected:

	public:
	Signal(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "signal", nLine, msgBox)
	{	
	}

	virtual void createTree() {};
	virtual void reorganizeLexemes() {};
};
#endif
