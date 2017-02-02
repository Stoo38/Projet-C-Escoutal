#ifndef _BLOC_H_
#define _BLOC_H_

#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>
#include <stdio.h>
#include <stdlib.h>

#include "Lexeme.h"
#include "../../DISPLAY/Display.h"

using namespace std;
//Classe virtuelle pure de base pour decouper le fichier VHDL
class Bloc
{
protected:
	//ATTRIBUTS
	Lexeme m_keyword;		//Contient le mot-clé de la classe 
	Lexeme m_identifiant;		//Contient l'identifiant et la premiere ligne de l'objet
	list <Lexeme> m_listLexemes;	//Contient les lexemes lies à l'objet
	Display &m_msgBox;		//Reference vers l'objet stockant les messages


public:
	//CONSTRUCTEURS
	Bloc(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	m_msgBox(msgBox)
	{	
		Lexeme key(motCle, nLine);
		Lexeme id(identifiant, nLine);			
		verifyLabel(id);		//Verification que l'identifiant est correct
		m_keyword = key;
		m_identifiant = id;		//Initialisation de l'identifiant		
		m_listLexemes.push_back(key);	//Ajout du premier lexeme, correspondant toujours au mot-cle
		m_listLexemes.push_back(id);	//Ajout du second lexeme, correspondant toujours a un identifiant
	}


	//ACCESSEURS
	const string & getIdentifiant() const;		//Renvoie l'identifiant
	const string getKeyWord() const;		//Renvoie le nom du bloc

	//MODIFIEURS
	void addLexeme(string lexeme, int nLine);	//Rajoute un lexeme et sa ligne a la liste

	//METHODES
	int trySpecialCharacter(Lexeme lex);		//Indique si le lexeme transmis est un caractere special: 1 pour oui, 0 pour non
	bool verifyFirstCharacter(Lexeme lex);		//Test le premier caractere du mot, et renvoie une erreur si ce n'est pas une lettre 
	bool verifyUnderscore(Lexeme lex);		//Test s'il n'y a pas d'underscore en début et/ ou fin du lexeme
	bool verifyGlobalWord(Lexeme lex);		//Test si le mot n'est composé que de lettres, chiffres ou underscores	
	bool verifyLabel(Lexeme lex);			//Test si le lexeme respecte les differentes regles pour une etiquette
	bool compareKeyWords(Lexeme lex);		//Test si le lexeme est egal à un mot-clé
	string checkNextWord(int count, list<Lexeme>::iterator itr);
	bool verifyNumber(string word);

	virtual void displayLexemes();			//Affiche chaque lexeme avec la ligne correspondante

	virtual void createTree() = 0;			//Prototype de la fonction de création de l'arbre
	virtual void reorganizeLexemes() = 0;		//Prototype de la fonction pour reorganiser les lexemes
	virtual void verifySyntax() = 0;		//Prototype de la fonction pour verifier la syntaxe

	virtual const string & getEntity() const {};	//Prototype de la fonction utilisee dans architecture
};

#endif	
