#ifndef _PROCESS_H_
#define _PROCESS_H_


#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>

#include "Lexeme.h"
#include "BlocInstruction.h"
#include "InstructionIf.h"
#include "InstructionCase.h"
#include "InstructionAssig.h"
#include "Variable.h"
#include "../../DISPLAY/Display.h"

using namespace std;

class Process : public BlocInstruction
{
	protected:

	public:
	Process(const string & identifiant, const int nLine, Display &msgBox):
	BlocInstruction(identifiant, "process", nLine, msgBox)
	{	
	}
	
	virtual void reorganizeLexemes();	
	virtual void createIfCase();
	virtual void createVariable();
	virtual void createAssig();
	virtual void verifySyntax();
};
#endif
