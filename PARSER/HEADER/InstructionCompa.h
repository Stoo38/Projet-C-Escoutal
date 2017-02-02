#ifndef _INSTRUCTIONCOMPA_H_
#define _INSTRUCTIONCOMPA_H_

#include "BlocInstruction.h"

using namespace std;
//Classe pour separer les comparaisons VHDL dans les if
class InstructionCompa : public BlocInstruction
{
	protected:

	public:
	InstructionCompa(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructioncompa", nLine, msgBox)
	{	

	}
	
	virtual void reorganizeLexemes();
	virtual void verifySyntax() {};
};
#endif
