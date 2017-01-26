#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>
#include "Lexeme.h"
#include "Bloc.h"
#include "../../DISPLAY/Display.h"

using namespace std;

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

	//ACCESSEURS

	//MODIFIEURS
	virtual void reorganizeLexemes() {};
	virtual void verifySyntax();
};
#endif
