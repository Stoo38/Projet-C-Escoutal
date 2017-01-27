#include "../HEADER/BlocInstruction.h"

void BlocInstruction::createTree()
{
	createVariable();
	createIf();
	createAssig();
	createComparison();
	BlocNode::createTree();
}

