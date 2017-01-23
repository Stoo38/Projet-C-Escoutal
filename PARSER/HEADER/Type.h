#ifndef _TYPE_H_
#define _TYPE_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Type : public Bloc
{
	protected:

	public:
	Type(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "type", nLine, msgBox)
	{	
	}

};
#endif
