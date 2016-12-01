#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

class Entity
{
protected:
	//ATTRIBUTS
	string m_identifiant;
	list < string > m_listeLexemes;

	//faire un tableau dynamique pour les key words roya

public:
	//CONSTRUCTEURS
	Entity(const string & identifiant = ""):
	m_identifiant(identifiant)
	{	
	}

	//ACCESSEURS
	void getIdentifiant() const;

	//MODIFIEURS
	void addLexeme(string lexeme);


};
#endif
