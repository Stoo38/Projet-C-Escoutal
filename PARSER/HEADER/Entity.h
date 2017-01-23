#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocNode.h"
#include "Port.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Entity : public BlocNode
{
	protected:

	public:
	Entity(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "entity", nLine, msgBox)
	{	
	}

	virtual void createTree();
};
#endif
