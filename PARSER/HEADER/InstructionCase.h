#ifndef _INSTRUCTIONCASE_H_
#define _INSTRUCTIONCASE_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocInstruction.h"
#include "InstructionIf.h"
#include "InstructionAssig.h"
#include "../../DISPLAY/Display.h"

using namespace std;

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
};
#endif
