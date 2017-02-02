#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Port.h"
#include "BlocNode.h"

using namespace std;
//Classe pour separer les component VHDL
class Component : public BlocNode
{
	protected:

	public:
	Component(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "component", nLine, msgBox)
	{	
	}

	//METHODE HERITEE
	virtual void createTree();
	virtual void verifySyntax();
};
#endif
