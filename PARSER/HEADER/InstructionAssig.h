#ifndef _INSTRUCTIONASSIG_H_
#define _INSTRUCTIONASSIG_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocInstruction.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class InstructionAssig : public BlocInstruction
{
	protected:

	public:
	InstructionAssig(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructionassig", nLine, msgBox)
	{	

	}
	
	virtual void reorganizeLexemes();
};
#endif
