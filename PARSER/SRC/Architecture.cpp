#include "../HEADER/Architecture.h"

void Architecture::createTree()
{
	createComponent();
	createProcess();
	createType();
	createSignal();
	BlocNode::createTree();
}
void Architecture::createComponent()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inComponent = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "component")
		{
			inComponent = true;
			itr++;
			m_listeBlocks.push_back(new Component((*itr).m_word, (*itr).m_line, m_msgBox));
			Lexeme flag("FLAG_COMP", (*itr).m_line);			 
			newList.push_back(flag);
			m_msgBox.createMessage("020", (*itr).m_line, (*itr).m_word);			
		}
		else if (((*itr).m_word == "end") && (inComponent == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "component")
			{
				itr++;
				if ((*itr).m_word == ";")
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else
				{
					m_msgBox.createMessage("022", (*itr).m_line, "");
					newList.push_back(*itr);
				}
				inComponent = false;
			}
			else
			{
				m_msgBox.createMessage("022", (*itr).m_line, "");
			}
		}
		else 
		{
			if (inComponent == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			}
			else
			{
				newList.push_back(*itr);
			}
		}	
	}
	m_listLexemes = newList;
}

void Architecture::createProcess()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inProcess = false;	
	bool labelProcess = false;		
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "process")
		{
			inProcess = true;
			itr--;
			if ((*itr).m_word == ":")
			{
				labelProcess = true;
				itr--;
				m_listeBlocks.push_back(new Process((*itr).m_word, (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("021", (*itr).m_line, (*itr).m_word);	
				itr++;
				itr++;
				newList.pop_back();
				newList.pop_back();				
			}
			else
			{
				itr++;
				m_listeBlocks.push_back(new Process("default", (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("021", (*itr).m_line, "default");				
			}
			
			Lexeme flag("FLAG_PROC", (*itr).m_line);			 
			newList.push_back(flag);
		}
		else if (((*itr).m_word == "end") && (inProcess == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "process")
			{
				itr++;
				if ((labelProcess == false) && ((*itr).m_word == ";"))
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else if ((labelProcess == true) && ((*itr).m_word == ";"))
				{
					m_msgBox.createMessage("026", (*itr).m_line, "");
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else if ((labelProcess == true) && ((*itr).m_word != ";"))
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
					itr++;
					if ((*itr).m_word == ";")
					{
						(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);							
					}
					else
					{
						m_msgBox.createMessage("027", (*itr).m_line, "");
						newList.push_back(*itr);
					}
				}
				else
				{
					m_msgBox.createMessage("024", (*itr).m_line, "");
					newList.push_back(*itr);
				}
				inProcess = false;
				labelProcess = false;
			}
		}
		else 
		{
			if (inProcess == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			}
			else
			{
				newList.push_back(*itr);
			}
		}
	}	
	m_listLexemes = newList;
}

void Architecture::createType()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inType = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "type")
		{
			inType = true;
			itr++;
			m_listeBlocks.push_back(new Type((*itr).m_word, (*itr).m_line, m_msgBox));
			m_msgBox.createMessage("802", (*itr).m_line, (*itr).m_word);	
			Lexeme flag("FLAG_TYPE", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inType == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inType = false;
		}
		else 
		{
			if (inType == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			}
			else
			{
				newList.push_back(*itr);
			}
		}	
	}
	m_listLexemes = newList;
}
void Architecture::createSignal()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inSignal = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "signal")
		{
			inSignal = true;
			itr++;
			m_listeBlocks.push_back(new Signal((*itr).m_word, (*itr).m_line, m_msgBox));
			m_msgBox.createMessage("801", (*itr).m_line, (*itr).m_word);	
			Lexeme flag("FLAG_SIGN", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inSignal == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inSignal = false;
		}
		else 
		{
			if (inSignal == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			}
			else
			{
				newList.push_back(*itr);
			}
		}	
	}
	m_listLexemes = newList;
}
