#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>

#include "PARSER/HEADER/Top.h"		
#include "DISPLAY/Display.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Création et initialisation des différents paramètres / options du menu
	int opt_nb_file = 1;			//Nombre de fichier VHDL à synthétiser
	bool opt_close_error = true;		//Option pour arrêter/ continuer quand l'on rencontre une erreur
	bool opt_debug = false;			//Option pour utiliser les messages de debug
	bool step_tree = false;			//Option pour activer l'étape de création de l'arbre, obligatoire pour passer aux étapes suivantes
	list <string> file;			// Liste contenant les différents fichiers VHDL à synthétiser
	

	// Récupération des différents paramètres passés depuis la ligne de commande
	int i = 1;
	string parameter;
	for(int i = 1; i < argc; i++)
	{
		parameter = argv[i];
		if (parameter == "-file")		// Paramètre utilisé pour indiquer le/ les différent(s) fichier(s) à synthétiser
		{
			for (int j = i; j < argc; j++)
			{
				string parameter2 = argv[j];
				if (parameter2 == "-nb_files")		// Recherche du paramètre -nb_files pour connaitre le nombre de fichiers à récupérer (par défaut 1)
				{	
					opt_nb_file = atoi(argv[j+1]);									
					j = argc;					
				}
			}
			for (int j = 0; j < opt_nb_file; j++)		// Récupération et stockage des différents fichiers VHDL
			{
				i++;
				file.push_back(argv[i]);					
			}					
		}
		else if (parameter == "-nb_files")	// Paramètre utilisé pour indiquer le nombre de fichiers VHDL
		{
			i++;	
			opt_nb_file = atoi(argv[i]);
		}
		else if (parameter == "-tree")		// Paramètre utilisé pour activer l'étape de création de l'arbre (par défaut true)
		{
			step_tree = true;	
		}
		else if (parameter == "-error")		// Paramètre utilisé pour continuer lors d'une erreur
		{
			opt_close_error = false;	
		}
		else if (parameter == "-debug")		// Paramètre utilisé pour continuer lors d'une erreur
		{
			opt_debug = true;	
		}
		else					// Sinon, paramètre non reconnu 
		{
			cout << "invalid parameter" << endl;
		}
	}

	// Déclenchement des différentes étapes de synthèse en utilisant les options définies précédemment
	list <string>::iterator itfile;
	Display messageBox(opt_close_error, opt_debug);			// Création de l'objet contenant tous les messages
	for (itfile = file.begin(); itfile != file.end(); itfile++) 	// Parcours un à un des fichiers VHDL
	{
		if (step_tree == true)					// Etape de création de l'arbre si l'option est activée
		{
			messageBox.createMessage("001", 0, *itfile);			
			Top myTop(*itfile, messageBox);				// Création d'un objet Top où toutes les informations pour un unique fichier VHDL seront stockées 
			myTop.createTree();					// Création de l'arbre en lui-même	
			myTop.reorganizeLexemes();	
			myTop.verifySyntax();	
			myTop.displayLexemes();
		}
	}
		
}



