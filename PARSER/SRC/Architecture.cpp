#include "../HEADER/Architecture.h"
void Architecture::displayLexemes()
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

void Architecture::createTree()
{
	createComponent();
	//createProcess();
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
			Lexeme flag("flag_component", (*itr).m_line);			 
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
	/*list <Lexeme>::iterator itr;
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
				proc_label = true;
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
			
			Lexeme flag("flag_process", (*itr).m_line);			 
			newList.push_back(flag);
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
	m_listLexemes = newList;*/
}
/*void Architecture::createTree()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool proc_label = false;
	string position("architecture");
	int countest = 0;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		cout << (*itr).m_word << " " << (*itr).m_line << " " << countest <<endl;
		if ((*itr).m_word == "component")
		{
			position = "component";
			itr++;
			m_listeBlocks.push_back(new Component((*itr).m_word, (*itr).m_line, m_msgBox));
			Lexeme flag("flag_component", (*itr).m_line);			 
			newList.push_back(flag);
			m_msgBox.createMessage("020", (*itr).m_line, (*itr).m_word);			
		}
		else if ((*itr).m_word == "process")
		{
			position = "process";
			itr--;
			if ((*itr).m_word == ":")
			{
				proc_label = true;
				itr--;
				m_listeBlocks.push_back(new Process((*itr).m_word, (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("021", (*itr).m_line, (*itr).m_word);	
				itr++;
				itr++;
				m_listLexemes.pop_back();
				m_listLexemes.pop_back();				
			}
			else
			{
				itr++;
				m_listeBlocks.push_back(new Process("default", (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("021", (*itr).m_line, "default");				
			}
			
			Lexeme flag("flag_process", (*itr).m_line);			 
			newList.push_back(flag);
		}
		else if (((*itr).m_word == "end") && (position == "component"))
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
					position = "architecture";
				}
				else
				{
					m_msgBox.createMessage("022", (*itr).m_line, "");
					position = "architecture";
					newList.push_back(*itr);
				}
			}
			else
			{
				m_msgBox.createMessage("022", (*itr).m_line, "");
			}
		}
		else if (((*itr).m_word == "end") && (position == "process"))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "process")
			{
				itr++;
				if ((proc_label == false) && ((*itr).m_word == ";"))
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else if ((proc_label == true) && ((*itr).m_word == ";"))
				{
					m_msgBox.createMessage("026", (*itr).m_line, "");
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else if ((proc_label == true) && ((*itr).m_word != ";"))
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
				position = "architecture";
				proc_label = false;
			}
		}
		else 
		{
			if ((position == "component") || (position == "process"))	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			}
			else
			{
				newList.push_back(*itr);
			}
		}
	countest++;				 
	}
	m_listLexemes = newList;
}*/
