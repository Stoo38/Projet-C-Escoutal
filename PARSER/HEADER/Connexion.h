#ifndef _CONNEXION_H_
#define _CONNEXION_H_

#include "BlocInstruction.h"
#include "Gate.h"

using namespace std;
//Classe pour separer les connexions VHDL entre signaux
class Connexion : public BlocInstruction
{
	protected:
	Gate m_gate;

	public:
	Connexion(const int nLine, Display &msgBox):
	BlocInstruction("default", "connexion", nLine, msgBox),
	m_gate(nLine, msgBox)
	{	
	}

	//METHODE HERITEE
	virtual void createTree();
	virtual void verifySyntax();
	virtual void displayLexemes();
	virtual void reorganizeLexemes() { m_gate.reorganizeLexemes();};
};
#endif
