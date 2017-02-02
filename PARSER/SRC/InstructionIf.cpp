#include "../HEADER/InstructionIf.h"

void InstructionIf::createAssig()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inAssig = false;
	
	int count = 0;
	string word;
	string nextWord;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		word = (*itr).m_word;
		nextWord = checkNextWord(count, itr);
		if ((word == "<") && (nextWord == "=") && (inAssig == false))
		{
			inAssig = true;
			m_listeBlocks.push_back(new InstructionAssig((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("812", (*itr).m_line, "");				
			itr--;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			newList.pop_back();
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			Lexeme flag("FLAG_ASSIG", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if ((word == ":") && (nextWord == "=") && (inAssig == false))
		{
			inAssig = true;
			m_listeBlocks.push_back(new InstructionAssig((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("812", (*itr).m_line, "");	
			itr--;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			newList.pop_back();
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	
			Lexeme flag("FLAG_ASSIG", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inAssig == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inAssig = false;			
		}
		else 
		{
			if (inAssig == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			}
			else
			{
				newList.push_back(*itr);
			}
		}	
		count++;
	}
	m_listLexemes = newList;
}

void InstructionIf::reorganizeLexemes()
{
	Lexeme mem("if", (m_listLexemes.front()).m_line);
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	m_listLexemes.push_front(mem);
	BlocNode::reorganizeLexemes();
}

void InstructionIf::createComparison()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inCompa = false;
	bool flagBegin = true;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if (((*itr).m_word == "default") && (inCompa == false))
		{
			if (flagBegin == true)
			{				
				inCompa = true;
				flagBegin = false;
				newList.push_back(*itr);
				m_listeBlocks.push_back(new InstructionCompa((*itr).m_line, m_msgBox));
				m_msgBox.createMessage("813", (*itr).m_line, "");
				Lexeme flag("FLAG_COMPA", (*itr).m_line);			 
				newList.push_back(flag);
			}
			else
			{
				newList.push_back(*itr);
			}			
		}
		else if (((*itr).m_word == "elsif") && (inCompa == false))
		{
			inCompa = true;
			newList.push_back(*itr);
			m_listeBlocks.push_back(new InstructionCompa((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("813", (*itr).m_line, "");
			Lexeme flag("FLAG_COMPA", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inCompa == true))
		{
			m_msgBox.createMessage("031", (*itr).m_line, "");
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inCompa = false;
		}
		else if (((*itr).m_word == "then") && (inCompa== true))
		{
			newList.push_back(*itr);
			inCompa = false;			
		}
		else 
		{
			if (inCompa == true)	
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

void InstructionIf::createIfCase()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inIf = false;	
	int countIf = 0;
	bool inCase = false;	
	int countCase = 0;		
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if (((*itr).m_word == "if") && (inIf == false) && (inCase == false))
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
		else if (((*itr).m_word == "case") && (inIf == false) && (inCase == false))
		{
			inCase = true;
			m_listeBlocks.push_back(new InstructionCase((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("814", (*itr).m_line, "");	
			Lexeme flag("FLAG_CASE", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == "case") && (inCase == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			countIf++;			
		}
		else if (((*itr).m_word == "end") && (inCase == true) && (countCase == 0))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "case")
			{
				itr++;
				if ((*itr).m_word == ";")
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else
				{
					m_msgBox.createMessage("032", (*itr).m_line, "");
					newList.push_back(*itr);
				}
				inCase = false;
			}
		}
		else if (((*itr).m_word == "end") && (inCase == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "case")
			{
				countCase--;
			}
		}
		else if ((*itr).m_word == "end")
		{
			newList.push_back(*itr);
			itr++;
			newList.push_back(*itr);
		}
		else 
		{
			if ((inIf == true) || (inCase == true))	
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



void InstructionIf::verifySyntax() 
{	
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;	
	bool flagElse = false;

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
			
		if (nbLexeme == 0)
		{
			if (nextWord != "FLAG_COMPA")
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)
		{
			if (nextWord != "then")
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;				
		}	

		else if (nbLexeme == 2)
		{
			if ((nextWord != "FLAG_IF") && (nextWord != "FLAG_CASE") && (nextWord != "FLAG_ASSIG"))
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;				
		}	

		else if (nbLexeme == 3)
		{
			if ((nextWord == "FLAG_IF") || (nextWord == "FLAG_CASE") || (nextWord == "FLAG_ASSIG"))
			{	
				nbLexeme = 3;
			}
			else if ((nextWord == "elsif") && (flagElse == false))
			{	
				nbLexeme = 4;
			}
			else if ((nextWord == "else") && (flagElse == false))
			{	
				nbLexeme = 5;
			}
			else if (nextWord == "end")
			{	
				nbLexeme = 6;
			}

			else
			{
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}			
		}			

		else if (nbLexeme == 4)
		{
			if (nextWord != "FLAG_COMPA")
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;				
		}	
	
		else if (nbLexeme == 5)
		{
			flagElse = true;
			if ((nextWord != "FLAG_IF") && (nextWord != "FLAG_CASE") && (nextWord != "FLAG_ASSIG"))
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;				
		}		

		else if (nbLexeme == 6)
		{
			if (nextWord != "if")
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 7;				
		}

		else if (nbLexeme == 7)
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("226", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 8;				
		}	

		else if (nbLexeme == 8)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("227", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}		
		count++;	
	}
	BlocNode::verifySyntax();
}

