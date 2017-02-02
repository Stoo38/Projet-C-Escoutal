#include "../HEADER/BlocInstruction.h"

void BlocInstruction::createTree()
{
	createVariable();
	createIfCase();
	createComparison();
	createAssig();	
	BlocNode::createTree();
}

