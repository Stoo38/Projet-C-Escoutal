#include "../HEADER/BlocInstruction.h"

void BlocInstruction::createTree()
{
	createVariable();
	createIfCase();
	createAssig();
	createComparison();
	BlocNode::createTree();
}

