#include "../HEADER/Entity.h"

void Entity::createTree()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inPort = false;	
	int countParenthesis = 0;		
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "port")
		{
			newList.push_back(*itr);
			itr++;
			if ((*itr).m_word == "(")
			{
				newList.push_back(*itr);
				itr++;
				m_listeBlocks.push_back(new Port((*itr).m_word, (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("803", (*itr).m_line, (*itr).m_word);		

			}
			else
			{
				cout << "error 1" << endl;
			}
			inPort = true;
			Lexeme flag("FLAG_PORT", (*itr).m_line);			 
			newList.push_back(flag);	
		}
		else if (((*itr).m_word == "(") && (inPort == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			countParenthesis++;
		}
		else if (((*itr).m_word == ")") && (countParenthesis > 0))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			countParenthesis--;
		}
		else if (((*itr).m_word == ")") && (countParenthesis == 0))
		{
			newList.push_back(*itr);
			inPort = false;
		}
		else if (((*itr).m_word == ";") && (inPort == true))
		{
			
			newList.push_back(*itr);
			itr++;
			m_listeBlocks.push_back(new Port((*itr).m_word, (*itr).m_line, m_msgBox));
			m_msgBox.createMessage("803", (*itr).m_line, (*itr).m_word);
			Lexeme flag("FLAG_PORT", (*itr).m_line);			 
			newList.push_back(flag);
		}
		else 
		{
			if (inPort == true)	
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
