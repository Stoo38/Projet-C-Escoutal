#ifndef _ARCHITECTURE_H_
#define _ARCHITECTURE_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocNode.h"
#include "Component.h"
#include "Process.h"
#include "Type.h"
#include "Signal.h"
#include "PortMap.h"
#include "Connexion.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Architecture : public BlocNode
{
	protected:
	Lexeme m_entity;	

	public:
	Architecture(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "architecture", nLine, msgBox)
	{	
	}

	virtual const string & getEntity() const;

	virtual void createTree();
	void createComponent();
	void createProcess();
	void createType();
	void createSignal();
	void createPortMap();
	void createConnexion();

	virtual void verifySyntax();
};
#endif
