#ifndef _BLOCINSTRUCTION_H_
#define _BLOCINSTRUCTION_H_

#include "BlocNode.h"

using namespace std;
//Classe de base utilisee pour les instructions dans le process
class BlocInstruction : public BlocNode
{
	protected:

	public:
	BlocInstruction(const string & identifiant, const string & motCle, const int nLine, Display &msgBox):
	BlocNode(identifiant, motCle, nLine, msgBox)
	{	
		
	}
	virtual void createTree();		//CreateTree identique pour toutes les instructions
	virtual void createIfCase() {};		//Prototype de la fonction qui permet de detecter les if et les case
	virtual void createVariable() {};	//Prototype de la fonction qui permet de detecter les variables
	virtual void createAssig() {};		//Prototype de la fonction qui permet de detecter les assignations
	virtual void createComparison() {};	//Prototype de la fonction qui permet de detecter les assignations
};
#endif
