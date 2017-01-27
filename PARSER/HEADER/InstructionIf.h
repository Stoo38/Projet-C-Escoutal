#ifndef _INSTRUCTIONIF_H_
#define _INSTRUCTIONIF_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocInstruction.h"
#include "InstructionAssig.h"
#include "InstructionCompa.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class InstructionIf : public BlocInstruction
{
	protected:

	public:
	InstructionIf(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructionif", nLine, msgBox)
	{	

	}

	virtual void createIf();
	virtual void createAssig();	
	virtual void reorganizeLexemes();
	virtual void createComparison();
};
#endif
