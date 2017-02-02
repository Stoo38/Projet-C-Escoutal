#include "../HEADER/PortMap.h"

void PortMap::reorganizeLexemes()
{
	m_listLexemes.pop_front();
}

void PortMap::verifySyntax()
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
			if (nextWord != ":")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;				
		}

		else if (nbLexeme == 2)
		{
			if (nextWord != "port")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;				
		}

		else if (nbLexeme == 3)
		{
			if (nextWord != "map")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;			
		}

		else if (nbLexeme == 4)
		{
			if (nextWord != "(")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;				
		}

		else if (nbLexeme == 5)
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;				
		}

		else if (nbLexeme == 6)
		{	
			if (nextWord == ",")
			{	
				nbLexeme = 7;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
					
		}	

		else if (nbLexeme == 7)
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
			nbLexeme = 6;			
		}

		else if (nbLexeme == 8)
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
			nbLexeme = 9;			
		}	

		else if (nbLexeme == 9)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("222", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}		
		count++;	
	}
}
