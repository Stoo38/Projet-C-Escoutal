#ifndef _BLOCNODE_H_
#define _BLOCNODE_H_

#include "Bloc.h"

using namespace std;
//Classe de base pour decouper le fichier VHDL et creer des noeuds
class BlocNode : public Bloc
{
	protected:
	list <Bloc *> m_listeBlocks;	//Liste de blocs contenus par le noeud

	public:
	BlocNode(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	Bloc(identifiant, motCle, nLine, msgBox)
	{	
		
	}
	//Prototype des fonctions créés dans Bloc et adaptées pour les noeuds
	//--> Elles appellent automatiquement les fonctions des Blocs contenus dans m_listeBlocks
	//METHODE HERITEE
	virtual void displayLexemes();
	virtual void createTree();
	virtual void reorganizeLexemes();
	virtual void verifySyntax();
};
#endif
