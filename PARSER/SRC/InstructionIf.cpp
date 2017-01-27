#include "../HEADER/InstructionIf.h"

void InstructionIf::createIf()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	newList.push_back(m_listLexemes.front());
	m_listLexemes.pop_front();
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
		else if ((*itr).m_word == "end")
		{
			newList.push_back(*itr);
			itr++;
			newList.push_back(*itr);
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

}
