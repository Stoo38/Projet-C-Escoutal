#ifndef _TOP_H_
#define _TOP_H_

#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>

#include "Bloc.h"
#include "Library.h"
#include "Entity.h"
#include "Architecture.h"
#include "../../DISPLAY/Display.h"
#include "functions.h"


using namespace std;

class Top
{
	private:
	string m_vhdlFileName;			//Nom du fichier VHDL
	Display &m_msgBox;			//Nom de l'objet contenant les messages
	list <Bloc *> m_listeBlocks;		//Liste des différents blocs composant l'arbre

	public:
	Top(const string vhdlFileName, Display &msgBox):	//Constructeur de Top avec deux paramètres: le nom du fichier et une boite d'erreur 
	m_vhdlFileName(vhdlFileName),
	m_msgBox(msgBox)
	{
		m_listeBlocks.clear();	
	}
	//Fonction utilisee pour creer les différents blocs en fonction des lexemes extraits du fichier VHDL
	void createTree();

	//Fonction instanciant des objets Entity, Library ou Architecture en fonction du fichier VHDL et les place dans m_listBlocks
	void instanceClass(vector<string> tab, int nLine);
	//Fonction l'affichage de tous les lexèmes contenus dans les blocks de m_listBlocks
	void displayLexemes();
	void verifySyntax();
};

#endif	
