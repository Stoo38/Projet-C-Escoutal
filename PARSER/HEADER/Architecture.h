#ifndef _ARCHITECTURE_H_
#define _ARCHITECTURE_H_

#include "BlocNode.h"
#include "Component.h"
#include "Process.h"
#include "Type.h"
#include "Signal.h"
#include "PortMap.h"
#include "Connexion.h"

using namespace std;
//Classe pour separer les architectures VHDL
class Architecture : public BlocNode
{
	protected:
	Lexeme m_entity;	//Contient le nom de l'entity liée

	public:
	Architecture(const string & identifiant, const int nLine, Display &msgBox):
	BlocNode(identifiant, "architecture", nLine, msgBox)
	{	
	}

	virtual const string & getEntity() const;

	virtual void createTree();
	void createComponent();		//Sépare les component
	void createProcess();		//Sépare les process
	void createType();		//Sépare les déclarations de types
	void createSignal();		//Sépare les déclarations de signaux
	void createPortMap();		//Sépare les port map
	void createConnexion();		//Sépare les connexions de signaux

	virtual void verifySyntax();
};
#endif
