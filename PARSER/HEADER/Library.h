#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>
#include "Lexeme.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Library : public Bloc
{
protected:
	//ATTRIBUTS

	//faire un tableau dynamique pour les key words roya

public:
	//CONSTRUCTEURS
	Library(const string & identifiant = "", const string & motCle = ""):
	Bloc(identifiant, motCle)
	{	
	}

	//ACCESSEURS

	//MODIFIEURS


	void browseLexeme() const;

};
#endif
