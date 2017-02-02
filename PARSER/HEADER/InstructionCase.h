#ifndef _INSTRUCTIONCASE_H_
#define _INSTRUCTIONCASE_H_

#include "BlocInstruction.h"
#include "InstructionIf.h"
#include "InstructionAssig.h"

using namespace std;
//Classe pour separer les case VHDL
class InstructionCase : public BlocInstruction
{
	protected:

	public:
	InstructionCase(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructioncase", nLine, msgBox)
	{	

	}
	
	virtual void createIfCase();
	virtual void createAssig();	
	virtual void reorganizeLexemes();
	virtual void verifySyntax() {};
};
#endif
