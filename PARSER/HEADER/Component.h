#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

class Component
{
protected:
	//ATTRIBUTS
	string m_identifiant;
	list < string > m_listeLexemes;

	//faire un tableau dynamique pour les key words roya

public:
	//CONSTRUCTEURS
	Component(const string & identifiant = ""):
	m_identifiant(identifiant)
	{	
	}

	//ACCESSEURS
	void getIdentifiant() const;

	//MODIFIEURS
	void addLexeme(string lexeme);


};
#endif
