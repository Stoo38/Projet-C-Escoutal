#ifndef _TYPE_H_
#define _TYPE_H_

#include "Bloc.h"

using namespace std;
//Classe pour separer les type VHDL
class Type : public Bloc
{
	protected:

	public:
	Type(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "type", nLine, msgBox)
	{	
	}
	//METHODE HERITEE
	virtual void createTree() {};
	virtual void reorganizeLexemes() {};
	virtual void verifySyntax();
};
#endif
