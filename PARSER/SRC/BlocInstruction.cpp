#include "../HEADER/BlocInstruction.h"

void BlocInstruction::createTree()
{
	createVariable();
	createIf();
	createAssig();
	BlocNode::createTree();
}

