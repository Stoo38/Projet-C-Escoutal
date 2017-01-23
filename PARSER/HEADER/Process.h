#ifndef _PROCESS_H_
#define _PROCESS_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocNode.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Process : public BlocNode
{
	protected:

	public:
	Process(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "process", nLine, msgBox)
	{	
	}
	
	virtual void reorganizeLexemes();	
};
#endif
