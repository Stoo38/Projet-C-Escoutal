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
	//Fonction remplacant toutes les majuscules se trouvant dans le string en entree par des minuscules
	string toMinuscule(string word);
	//Fonction detectant un commentaire VHDL dans un string et effacant tous les caracteres correspondants
	string eraseComment(string sentence);
	//Fonction enlevant toutes les iterations d'un meme caractere dans un string
	string eraseCharacter(string sentence, const char symbol);
	//Fonction decoupant en fonction des espaces, puis supprimant toutes les chaines de caractères vides
	vector<string> eraseSpace(vector<string> tab);
	//Fonction decoupant en plusieurs string un vector<string> en entree, en fonction d'un caractere defini
	//EXEMPLE: Pour e: "Testest" ---> "T" "e" "st "e" "st"
	vector<string> cutCharacter(vector<string> tab, const char symbol);
	//Fonction decoupant en plusieurs string un vector<string> en entree, en fonction de tous les caractères spéciaux
	vector<string> cutSpecialCharacter(vector<string> tab);	

	void instanceClass(vector<string> tab, int nLine);
	void displayLexemes();
};

#endif	
