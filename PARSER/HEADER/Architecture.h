#ifndef _ARCHITECTURE_H_
#define _ARCHITECTURE_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "Component.h"
#include "Process.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Architecture : public Bloc
{
	protected:
	list <Bloc *> m_listeBlocks;

	public:
	Architecture(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "architecture", nLine, msgBox)
	{	
	}

	virtual void createTree();
	virtual void displayLexemes();
};
#endif
