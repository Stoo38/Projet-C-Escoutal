#ifndef _INSTRUCTIONCOMPA_H_
#define _INSTRUCTIONCOMPA_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocInstruction.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class InstructionCompa : public BlocInstruction
{
	protected:

	public:
	InstructionCompa(const int nLine, Display &msgBox):
	BlocInstruction("default", "instructioncompa", nLine, msgBox)
	{	

	}

	virtual void reorganizeLexemes();
};
#endif
