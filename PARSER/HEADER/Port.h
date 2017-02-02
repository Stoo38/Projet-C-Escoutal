#ifndef _PORT_H_
#define _PORT_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>
#include <stdio.h>
#include <stdlib.h>

#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Port : public Bloc
{
	protected:
	bool m_in;
	string m_type;
	int m_size_a;
	int m_size_b;

	public:
	Port(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "port", nLine, msgBox),
	m_in(true),
	m_type(""),
	m_size_a(0),
	m_size_b(0)
	{	
	}

	virtual void createTree() {};
	virtual void reorganizeLexemes();
	virtual void verifySyntax();
};
#endif
