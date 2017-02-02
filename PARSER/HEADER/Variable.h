#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "Bloc.h"

using namespace std;
//Classe pour separer les variables VHDL
class Variable : public Bloc
{
	protected:

	public:
	Variable(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "variable", nLine, msgBox)
	{	
	}
	//METHODE HERITEE
	virtual void createTree() {};
	virtual void reorganizeLexemes() {};
	virtual void verifySyntax();
};
#endif
