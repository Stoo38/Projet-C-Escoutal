#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <cstdlib>

#include "../PARSER/HEADER/functions.h"

using namespace std;

class Display
{
   	protected:
	bool m_closeError;				//Option pour fermer ou pas durant une erreur
   	string m_messageFileName;			//Chemin vers le fichier contenant le texte des messages
	list <string> m_listMessages;			//Liste des messages rencontrés et stockés
	int m_alreadyDisplayed;				//Marqueur pour savoir quels messages ont déjà été affichés
   	public:
   	Display(bool closeError = true) :		//Constructeur de Display
	m_closeError(closeError),
	m_messageFileName("DISPLAY/Messages_bastal.txt"), 	//Mettre le chemin absolu en cas de problème
	m_alreadyDisplayed(0)				//Pas de Message déjà affiché
   	{
		
   	}
	
	~Display()
	{
		displayMessage();
	}

    	void createMessage(string nMessage, int nline = 0, string lexeme = "");	//Permet d'ajouter un message à la liste et de quitter le programme selon l'erreur
	void displayMessage(bool allDisplay = false);				//Affiche les messages stockés, à partir du début ou seulement depuis le dernier affiché
};
#endif
