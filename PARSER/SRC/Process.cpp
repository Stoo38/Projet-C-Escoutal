#include "../HEADER/Process.h"

void Process::reorganizeLexemes()
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	
	if ((m_listLexemes.front()).m_word == ":")
	{
		m_listLexemes.pop_front();
	}
		
	Lexeme n1(":", m_identifiant.m_line);
	Lexeme n2("process", m_identifiant.m_line);
	m_listLexemes.push_front(n2);
	m_listLexemes.push_front(n1);	
	m_listLexemes.push_front(m_identifiant);
	BlocNode::reorganizeLexemes();
}

void Process::createVariable()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inVariable = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "variable")
		{
			inVariable = true;
			itr++;
			m_listeBlocks.push_back(new Variable((*itr).m_word, (*itr).m_line, m_msgBox));
			m_msgBox.createMessage("811", (*itr).m_line, (*itr).m_word);	
			Lexeme flag("FLAG_VARI", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inVariable == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inVariable = false;
		}
		else 
		{
			if (inVariable == true)	
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


void Process::createIf()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inIf = false;	
	int countIf = 0;		
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if (((*itr).m_word == "if") && (inIf == false))
		{
			inIf = true;
			m_listeBlocks.push_back(new InstructionIf((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("810", (*itr).m_line, "");	
			Lexeme flag("FLAG_IF", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == "if") && (inIf == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			countIf++;			
		}
		else if (((*itr).m_word == "end") && (inIf == true) && (countIf == 0))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "if")
			{
				itr++;
				if ((*itr).m_word == ";")
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else
				{
					m_msgBox.createMessage("030", (*itr).m_line, "");
					newList.push_back(*itr);
				}
				inIf = false;
			}
		}
		else if (((*itr).m_word == "end") && (inIf == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "if")
			{
				countIf--;
			}
		}
		else 
		{
			if (inIf == true)	
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
