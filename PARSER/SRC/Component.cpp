#include "../HEADER/Component.h"

void Component::createTree()
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
				m_msgBox.createMessage("029", (*itr).m_line, (*itr).m_word);
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


// Fonction qui effectue la vérification syntaxique 
void Component::verifySyntax() 
{	
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;	

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
		if (nbLexeme == 0)
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)
		{	
			if (nextWord == "port")
			{	
				nbLexeme = 2;
			}
			else if (nextWord == "end")
			{	
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
					
		}	

		else if (nbLexeme == 2)
		{
			if (nextWord != "(")
			{	
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
			nbLexeme = 3;			
		}	
	
		else if (nbLexeme == 3)
		{
			if (nextWord != "FLAG_PORT")
			{	
				m_msgBox.createMessage("203", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;
		}	
	
		else if (nbLexeme == 4)
		{
			if (nextWord == ";")
			{	
				nbLexeme = 5;
			}
			else if (nextWord == ")")
			{
				nbLexeme = 6;
			}
			else 
			{
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
		}	
	
		else if (nbLexeme == 5)
		{
			if (nextWord != "FLAG_PORT")
			{
				m_msgBox.createMessage("203", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;
		}

		else if (nbLexeme == 6)
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);	
				itr = m_listLexemes.end();
				itr--;	
			}
			nbLexeme = 7;

		}	

		else if (nbLexeme == 7)
		{
			if (nextWord != "end")
			{
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);	
				itr = m_listLexemes.end();
				itr--;	
			}
			nbLexeme = 8;
		}

		else if (nbLexeme == 8)
		{
			if (nextWord != "component")
			{	
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;
		}

		else if (nbLexeme == 9)
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 10;
		}

		else if (nbLexeme == 10)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("215", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}		
		count++;	
	}
	BlocNode::verifySyntax();
}
