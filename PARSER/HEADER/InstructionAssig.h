#ifndef _INSTRUCTIONASSIG_H_
#define _INSTRUCTIONASSIG_H_

#include "BlocInstruction.h"

using namespace std;
//Classe pour separer les assignations VHDL
class InstructionAssig : public BlocInstruction
{
	protected:

	public:
	InstructionAssig(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructionassig", nLine, msgBox)
	{	

	}
	//METHODE HERITEE
	virtual void reorganizeLexemes();
	virtual void verifySyntax() {};
};
#endif
