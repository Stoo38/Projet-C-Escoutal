#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Entity : public Bloc
{
	protected:

	public:
	Entity(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "entity", nLine, msgBox)
	{	
	}

};
#endif
