#include "../HEADER/BlocNode.h"

void BlocNode::displayLexemes()
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

void BlocNode::createTree() 
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

void BlocNode::reorganizeLexemes() 
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

void BlocNode::verifySyntax() 
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
