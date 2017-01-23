#ifndef _COMPONENT_H_
#define _COMPONENT_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocNode.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Component : public BlocNode
{
	protected:

	public:
	Component(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "component", nLine, msgBox)
	{	
	}

	virtual void createTree();
};
#endif
