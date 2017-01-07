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
	Lexeme m_identifiant;
	list <Lexeme> m_listLexemes;
	Display &m_msgBox;


public:
	//CONSTRUCTEURS
	Bloc(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	m_msgBox(msgBox)
	{	
		Lexeme id(identifiant, nLine);		
		verifyGlobalWord(id);		
		m_identifiant = id;
		addLexeme(motCle, nLine);
		m_listLexemes.push_back(id);
	}


	//ACCESSEURS
	const string & getIdentifiant() const;

	//MODIFIEURS
	void addLexeme(string lexeme, int nLine);

	//METHODES
	int trySpecialCharacter(Lexeme lex);
	void verifyFirstCharacter(Lexeme lex);
	void verifyUnderscore(Lexeme lex);
	void verifyGlobalWord(Lexeme lex);
	void displayLexemes();
};

#endif	
