#ifndef _BLOC_H_
#define _BLOC_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

class Bloc
{
protected:
	//ATTRIBUTS
	string m_identifiant;
	list < string > m_listeLexemes;

	//faire un tableau dynamique pour les key words roya

public:
	//CONSTRUCTEURS
	Bloc(const string & identifiant = ""):
	m_identifiant(identifiant)
	{	
	}

	//ACCESSEURS
	void getIdentifiant() const;

	//MODIFIEURS
	void addLexeme(string lexeme);


};

#endif	