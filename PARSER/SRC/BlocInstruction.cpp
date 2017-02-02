#include "../HEADER/BlocInstruction.h"

void BlocInstruction::createTree()	//Fonction de separation des variables, if, case et assignations pour toutes les instructions
{
	createVariable();
	createIfCase();
	createComparison();
	createAssig();	
	BlocNode::createTree();
}

