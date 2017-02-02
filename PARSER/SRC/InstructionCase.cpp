#include "../HEADER/InstructionCase.h"
//Fonction pour separer les if et les case
void InstructionCase::createIfCase()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inIf = false;	
	int countIf = 0;
	bool inCase = false;	
	int countCase = 0;		
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if (((*itr).m_word == "if") && (inIf == false) && (inCase == false))		//on detecte le debut d'un if
		{
			inIf = true;
			m_listeBlocks.push_back(new InstructionIf((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("810", (*itr).m_line, "");	
			Lexeme flag("FLAG_IF", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == "if") && (inIf == true))				//on detecte un if dans un if deja detecte
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			countIf++;			
		}
		else if (((*itr).m_word == "end") && (inIf == true) && (countIf == 0))		//on detecte la fin d'un if
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
		else if (((*itr).m_word == "end") && (inIf == true))			//on detecte la fin d'un if
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "if")
			{
				countIf--;
			}
		}
		else if (((*itr).m_word == "case") && (inIf == false) && (inCase == false))	//on detecte le debut d'un case
		{
			inCase = true;
			m_listeBlocks.push_back(new InstructionCase((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("814", (*itr).m_line, "");	
			Lexeme flag("FLAG_CASE", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == "case") && (inCase == true))				//on detecte le debut d'un case dans un case deja detecte
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			countIf++;			
		}
		else if (((*itr).m_word == "end") && (inCase == true) && (countCase == 0))	//on detecte la fin d'un case
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
		else if (((*itr).m_word == "end") && (inCase == true))		//on detecte la fin d'un case declare dans un case 
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
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//on ajoute les lexemes au dernier objet deja cree
			}
			else
			{
				newList.push_back(*itr);	//On ajoute les lexemes a la nouvelle liste
			}
		}	
	}
	m_listLexemes = newList;
}

void InstructionCase::createAssig()		//Separation des lexemes des assignations
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
		if ((word == "<") && (nextWord == "=") && (inAssig == false))	//On repère une assignation à partir des "<=" pour les signaux
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
		else if ((word == ":") && (nextWord == "=") && (inAssig == false))   //On repère une assignation à partir des ":=" pour les signaux
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
		else if (((*itr).m_word == ";") && (inAssig == true))	//On repere la fin d'une assignation avec le lexeme ";"
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inAssig = false;			
		}
		else 
		{
			if (inAssig == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout du lexeme a la derniere assignation creee
			}
			else
			{
				newList.push_back(*itr);	//Ajout du lexeme a la nouvelle liste
			}
		}	
		count++;
	}
	m_listLexemes = newList;
}

void InstructionCase::reorganizeLexemes()	//Reorganise les lexemes contenus dans l'instruction case
{
	Lexeme mem("case", (m_listLexemes.front()).m_line);
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	m_listLexemes.push_front(mem);
	BlocNode::reorganizeLexemes();
}
