#include "../HEADER/BlocInstruction.h"

void BlocInstruction::createTree()
{
	createVariable();
	createIf();
	BlocNode::createTree();
}

