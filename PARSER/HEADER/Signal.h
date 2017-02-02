#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include "Bloc.h"
#include "BlocNode.h"

using namespace std;
//Classe pour separer les déclarations de signaux VHDL
class Signal : public Bloc
{
	protected:

	public:
	Signal(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "signal", nLine, msgBox)
	{	
	}
	//METHODE HERITEE
	virtual void createTree() {};
	virtual void reorganizeLexemes() {};
	virtual void verifySyntax();
};
#endif
