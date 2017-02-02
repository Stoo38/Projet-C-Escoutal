#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "BlocNode.h"
#include "Port.h"

using namespace std;
//Classe pour separer les entity VHDL
class Entity : public BlocNode
{
	protected:

	public:
	Entity(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "entity", nLine, msgBox)
	{	
	}
	
	//METHODE HERITEE
	virtual void createTree();
	virtual void verifySyntax();
};
#endif
