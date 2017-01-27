#ifndef _BLOCINSTRUCTION_H_
#define _BLOCINSTRUCTION_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocNode.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class BlocInstruction : public BlocNode
{
	protected:

	public:
	BlocInstruction(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	BlocNode(identifiant, motCle, nLine, msgBox)
	{	
		
	}
	virtual void createTree();
	virtual void createVariable() {};
	virtual void createIf() {};
	virtual void createAssig() {};
	virtual void createComparison() {};
};
#endif
