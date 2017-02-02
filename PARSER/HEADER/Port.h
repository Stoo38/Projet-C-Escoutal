#ifndef _PORT_H_
#define _PORT_H_

#include "Bloc.h"

using namespace std;
//Classe pour separer les ports VHDL
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
	//METHODE HERITEE
	virtual void createTree() {};
	virtual void reorganizeLexemes();
	virtual void verifySyntax();
};
#endif
