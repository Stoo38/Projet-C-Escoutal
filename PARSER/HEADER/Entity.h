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
<<<<<<< HEAD

	virtual void createTree();
=======
	
	//METHODE HERITEE
	virtual void verifySyntax();
>>>>>>> 0861227b5c1539c99414fdfd6a44324b28122e42
};
#endif
