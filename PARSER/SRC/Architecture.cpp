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

void Architecture::distributeLexemes()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	string position("architecture");
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "component")
		{
			position = "component";
			itr++;
			m_listeBlocks.push_back(new Component((*itr).m_word, (*itr).m_line, m_msgBox));
			Lexeme flag("flag_component", (*itr).m_line);			 
			newList.push_back(flag);
			m_msgBox.createMessage("20", (*itr).m_line, (*itr).m_word);			
		}
		else if ((*itr).m_word == "process")
		{
			position = "process";
			itr--;
			if ((*itr).m_word == ":")
			{
				itr--;
				m_listeBlocks.push_back(new Process((*itr).m_word, (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("21", (*itr).m_line, (*itr).m_word);	
				itr++;
				itr++;
				m_listLexemes.pop_back();
				m_listLexemes.pop_back();				
			}
			else
			{
				itr++;
				m_listeBlocks.push_back(new Process("default", (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("21", (*itr).m_line, "default");				
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
					m_msgBox.createMessage("22", (*itr).m_line, "");
					position = "architecture";
					newList.push_back(*itr);
				}
			}
			else
			{
				m_msgBox.createMessage("22", (*itr).m_line, "");
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
				if ((*itr).m_word == ";")
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
					position = "architecture";
				}
				else
				{
					m_msgBox.createMessage("24", (*itr).m_line, "");
					position = "architecture";
					newList.push_back(*itr);
				}
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
	}
	m_listLexemes = newList;
}
