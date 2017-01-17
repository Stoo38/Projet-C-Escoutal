#ifndef _COMPONENT_H_
#define _COMPONENT_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Component : public Bloc
{
	protected:

	public:
	Component(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "component", nLine, msgBox)
	{	
	}

};
#endif
