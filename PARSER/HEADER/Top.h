#ifndef _TOP_H_
#define _TOP_H_

#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "Bloc.h"
#include <vector>

using namespace std;

class Top
{
	private:
	string m_vhdlFileName;
	//list < *Bloc > m_listeBlocks;

	public:
	Top(const string vhdlFileName = ""):
	m_vhdlFileName(vhdlFileName)
	{
		//m_listeBlocks.clear();	
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
	
};

#endif	
