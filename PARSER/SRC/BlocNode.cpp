#include "../HEADER/BlocNode.h"

void BlocNode::displayLexemes()		//Lance displayLexemes pour les Blocs contenus dans la liste
{
	Bloc::displayLexemes();
	if (m_listeBlocks.size() > 0)
	{
		list <Bloc *>::iterator it;
		for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
		{
			(*it)->displayLexemes();
		}
	}
}

void BlocNode::createTree() 		//Lance createTree pour les Blocs contenus dans la liste
{
	if (m_listeBlocks.size() > 0)
	{
		list <Bloc *>::iterator it;
		for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
		{
			(*it)->createTree();
		}
	}
}

void BlocNode::reorganizeLexemes() 	//Lance reorganizeLexemes pour les Blocs contenus dans la liste
{
	if (m_listeBlocks.size() > 0)
	{
		list <Bloc *>::iterator it;
		for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
		{
			(*it)->reorganizeLexemes();
		}
	}
}

void BlocNode::verifySyntax() 		//Lance verifySyntax pour les Blocs contenus dans la liste
{
	if (m_listeBlocks.size() > 0)
	{
		list <Bloc *>::iterator it;
		for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
		{
			(*it)->verifySyntax();
		}
	}
}
