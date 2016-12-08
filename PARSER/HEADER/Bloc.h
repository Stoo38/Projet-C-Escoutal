/* La classe Bloc est mère des classes Library, Entity, Architecture et Component.
Elle répertorie les fonctions et les attributs globaux 
*/ 



#ifndef _BLOC_H_
#define _BLOC_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

class Bloc
{
protected:
	//ATTRIBUTS
	string m_identifiant;
	list < string > m_listLexemes;
	int m_error;


public:
	//CONSTRUCTEURS
	Bloc(const string & identifiant = "", const string & motCle = "")
	{	
		m_error = verifyGlobalWord(identifiant);
		if (m_error == 0)
		{
			m_identifiant = identifiant;
			addLexeme(motCle);
			addLexeme(identifiant);
		}
		else
		{
			cout << "Erreur dans " << motCle << ": l'identifiant " << identifiant << " est incorrect !" << endl; 
			m_identifiant = "";
		}
			
	}


	//ACCESSEURS
	const string & getIdentifiant() const;
	const int & getError() const;

	//MODIFIEURS
	void addLexeme(string lexeme);

	//METHODES
	int trySpecialCharacter(string lexeme);
	int verifyFirstCharacter(string lexeme);
	int verifyUnderscore(string lexeme);
	int verifyGlobalWord(string lexeme);
	void displayLexemes();
};

#endif	
