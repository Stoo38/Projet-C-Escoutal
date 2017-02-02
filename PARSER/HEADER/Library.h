#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Bloc.h"

using namespace std;
//Classe pour separer les library VHDL
class Library : public Bloc
{
	protected:
	//ATTRIBUTS

	//faire un tableau dynamique pour les key words roya

	public:
	//CONSTRUCTEURS
	Library(const string & identifiant, const int nLine, Display &msgBox):
	Bloc(identifiant, "library", nLine, msgBox)
	{	
	}

	//METHODE HERITEE
	virtual void createTree() {};
	virtual void reorganizeLexemes() {};	
	virtual void verifySyntax();
};
#endif
