#ifndef _INSTRUCTIONIF_H_
#define _INSTRUCTIONIF_H_

#include "BlocInstruction.h"
#include "InstructionCase.h"
#include "InstructionAssig.h"
#include "InstructionCompa.h"

using namespace std;
//Classe pour separer les if VHDL
class InstructionIf : public BlocInstruction
{
	protected:

	public:
	InstructionIf(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructionif", nLine, msgBox)
	{	

	}

	virtual void createIfCase();
	virtual void createAssig();	
	virtual void reorganizeLexemes();
	virtual void createComparison();
	virtual void verifySyntax();
};
#endif
