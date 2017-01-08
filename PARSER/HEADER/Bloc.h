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
#include "Lexeme.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Bloc
{
protected:
	//ATTRIBUTS
	Lexeme m_identifiant;		//Contient l'identifiant et la premiere ligne de l'objet
	list <Lexeme> m_listLexemes;	//Contient les lexemes lies à l'objet
	Display &m_msgBox;		//Reference vers l'objet stockant les messages


public:
	//CONSTRUCTEURS
	Bloc(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	m_msgBox(msgBox)
	{	
		Lexeme id(identifiant, nLine);			
		verifyGlobalWord(id);		//Verification que l'identifiant est correct
		m_identifiant = id;		//Initialisation de l'identifiant
		addLexeme(motCle, nLine);	//Ajout du premier lexeme, correspondant toujours au mot-cle
		m_listLexemes.push_back(id);	//Ajout du second lexeme, correspondant toujours a un identifiant
	}


	//ACCESSEURS
	const string & getIdentifiant() const;		//Renvoie l'identifiant

	//MODIFIEURS
	void addLexeme(string lexeme, int nLine);	//Rajoute un lexeme et sa ligne a la liste

	//METHODES
	int trySpecialCharacter(Lexeme lex);		//Indique si le lexeme transmis est un caractere special: 1 pour oui, 0 pour non
	void verifyFirstCharacter(Lexeme lex);		//Test le premier caractere du mot, et renvoie une erreur si ce n'est pas une lettre 
	void verifyUnderscore(Lexeme lex);		// A ECRIRE
	void verifyGlobalWord(Lexeme lex);		// A ECRIRE
	void displayLexemes();				//Affiche chaque lexeme avec la ligne correspondante
	void verifyLabel(Lexeme lex);			// A ECRIRE
};

#endif	
