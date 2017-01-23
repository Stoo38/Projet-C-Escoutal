#ifndef _BLOCNODE_H_
#define _BLOCNODE_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "Port.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class BlocNode : public Bloc
{
	protected:
	list <Bloc *> m_listeBlocks;

	public:
	BlocNode(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	Bloc(identifiant, motCle, nLine, msgBox)
	{	
		
	}

	virtual void displayLexemes();
	virtual void createTree();
	virtual void reorganizeLexemes();
	virtual void verifySyntax();
};
#endif
