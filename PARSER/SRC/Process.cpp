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
	Lexeme n4(";", (m_listLexemes.back()).m_line);
	m_listLexemes.push_front(n2);
	m_listLexemes.push_front(n1);	
	m_listLexemes.push_front(m_identifiant);
	m_listLexemes.pop_back();
	if ((m_listLexemes.back()).m_word != m_identifiant.m_word)
	{
		Lexeme n3(m_identifiant.m_word, (m_listLexemes.back()).m_line);
		m_listLexemes.push_back(n3);
	}
	m_listLexemes.push_back(n4);
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

void Process::createAssig()
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

void Process::createIfCase()
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
			countCase++;			
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


void Process::verifySyntax() 
{	
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;	

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);

		cout << count << " " << m_listLexemes.size() << " " << nbLexeme << " " << monword << " " << nextWord <<  endl;
	
		if (nbLexeme == 0)
		{
			if (nextWord != ":")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)
		{
			if (nextWord != "process")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;				
		}	

		else if (nbLexeme == 2)
		{
			if (nextWord != "(")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;				
		}	

		else if (nbLexeme == 3)
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;				
		}		

		else if (nbLexeme == 4)
		{
			if (nextWord == ",")
			{	
				nbLexeme = 5;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 6;
			}
			else
			{
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}			
		}	
	
		else if (nbLexeme == 5)
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;				
		}	

		else if (nbLexeme == 6)
		{
			if (nextWord == "FLAG_VARI")
			{	
				nbLexeme = 7;
			}
			else if (nextWord == "begin")
			{	
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}				
		}	

		else if (nbLexeme == 7)
		{
			if (nextWord == "FLAG_VARI")
			{	
				nbLexeme = 7;
			}
			else if (nextWord == "begin")
			{	
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}				
		}	

		else if (nbLexeme == 8)
		{
			if ((nextWord == "FLAG_IF") || (nextWord == "FLAG_CASE") || (nextWord == "FLAG_ASSIG"))
			{	
				nbLexeme = 9;
			}
			else if (nextWord == "end")
			{	
				nbLexeme = 10;
			}
			else
			{
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}				
		}	

		else if (nbLexeme == 9)
		{
			if ((nextWord == "FLAG_IF") || (nextWord == "FLAG_CASE") || (nextWord == "FLAG_ASSIG"))
			{	
				nbLexeme = 9;
			}
			else if (nextWord == "end")
			{	
				nbLexeme = 10;
			}
			else
			{
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}				
		}

		else if (nbLexeme == 10)
		{
			if (nextWord != "process")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 11;
		}

		else if (nbLexeme == 11)
		{
			if (nextWord != m_identifiant.m_word)
			{	
				m_msgBox.createMessage("223", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 12;
		}

		else if (nbLexeme == 12)
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 13;
		}



		else if (nbLexeme == 13)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("224", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}		
		count++;	
	}
	BlocNode::verifySyntax();
}


