#ifndef _PORTMAP_H_
#define _PORTMAP_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class PortMap : public Bloc
{
	protected:
	Lexeme m_component;

	public:
	PortMap(const string & identifiant, const string & component, const int nLine, Display &msgBox):
	Bloc(identifiant, "portmap", nLine, msgBox)
	{
		Lexeme compo(component, nLine);			
		verifyLabel(compo);
		m_component = compo;
	}

	virtual void reorganizeLexemes();
};
#endif
