#ifndef _PORTMAP_H_
#define _PORTMAP_H_

#include "Bloc.h"

using namespace std;
//Classe pour separer les port map VHDL
class PortMap : public Bloc
{
	protected:
	Lexeme m_component;

	public:
	PortMap(const string & identifiant, const string & component, const int nLine, Display &msgBox):
	Bloc(identifiant, "portmap", nLine, msgBox)
	{
		Lexeme compo(component, nLine);			
		verifyLabel(compo);
		m_component = compo;
	}
	//METHODE HERITEE
	virtual void createTree() {};
	virtual void reorganizeLexemes();
	virtual void verifySyntax();
};
#endif
