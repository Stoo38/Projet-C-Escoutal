#include "../HEADER/Connexion.h"
//Affiche tous les lexemes contenu dans l'objet Gate
void Connexion::displayLexemes()
{
	BlocNode::displayLexemes();
	m_gate.displayLexemes();
}

//Instancie un objet Gate contenant la partie droite de la connexion
//L'objectif est de faire un arbre pour simplifier le traitement
void Connexion::createTree()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	itr = m_listLexemes.begin();
	itr++;
	itr++;
	newList.push_back(*itr);
	itr++;
	newList.push_back(*itr);
	itr++;
	newList.push_back(*itr);
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	Lexeme flag("FLAG_GATE", (*itr).m_line);			 
	newList.push_back(flag);

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{		
		if ((*itr).m_word != ";")
		{
			m_gate.addLexeme((*itr).m_word, (*itr).m_line);
		}
		else
		{
			newList.push_back(*itr);
		}
	}
	m_listLexemes = newList;
}

void Connexion::verifySyntax() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	
	string monword;
	string nextWord;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		monword = (*itr).m_word;
		nextWord = checkNextWord(count, itr);
		switch (nbLexeme)
		{
			case 0:						
					
				if (verifyLabel(monword) == false)	//Premier mot: nom du signal 
				{				
					if (nextWord == "<")			//Second mot: "<"
					{
						nbLexeme = 1;
					}
					else
					{
						m_msgBox.createMessage("236", (*itr).m_line, nextWord);
						itr = m_listLexemes.end();
						itr--;
					}
				}
				else
				{
					m_msgBox.createMessage("235", (*itr).m_line, monword);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 1:
				if (nextWord == "=")		//Prochain mot: "="
				{
					nbLexeme = 2;
				}
				else
				{
					m_msgBox.createMessage("236", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 2:
				if (nextWord == "FLAG_GATE")		//Prochain mot: "FLAG_GATE"
				{
					nbLexeme = 3;
				}
				else
				{
					m_msgBox.createMessage("236", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 3:
				if (nextWord == ";")		//Prochain mot: ";"
				{
					nbLexeme = 4;
				}
				else
				{
					m_msgBox.createMessage("236", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 4:
				if (nextWord == "")		//Pas de prochain mot
				{
					nbLexeme = 2;
				}
				else
				{
					m_msgBox.createMessage("237", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			default:
				break;
		}
		count++;
	}
	m_gate.verifySyntax();		
}
