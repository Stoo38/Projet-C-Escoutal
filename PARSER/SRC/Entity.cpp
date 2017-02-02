#include "../HEADER/Entity.h"

/* 
##################Void VerifySyntax()##################
Fonctionnement global expliqué dans Library.cpp
 */

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
				m_msgBox.createMessage("029", (*itr).m_line, "");
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
void Entity::verifySyntax() 
{
	
	list <Lexeme>::iterator itr; 	// Création de l'itérateur permettant de parcourir chaque lexeme du signal
	int nbLexeme = 0; 		// nbLexeme correspond aux différents états de la FSM
	int count = 0; 			// Le compteur permet de relever le nombre de fois que l'on a changé d'étape
	
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++) //Début du parcours d'une entité pour vérification
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);


		if (nbLexeme == 0) // CAS 0: Mot clef "Entity"
		{
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1) // CAS 1: Label correspondant à l'étiquette de l'entité
		{
			
			if (nextWord != "is")
			{	
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;
		
		}

		else if (nbLexeme == 2) // CAS 2: Mot clef "is"
		{	
			if (nextWord == "port")
			{	
				nbLexeme = 3;
			}
			else if (nextWord == "end")
			{	
				nbLexeme = 9;
			}
			else
			{
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
					
		}	

		else if (nbLexeme == 3) // CAS 3: Mot clef "port"
		{
			if (nextWord != "(")
			{	
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
			nbLexeme = 4;			
		}	
	
		else if (nbLexeme == 4) // CAS 4: Paranthèse ouvrante "("
		{
			if (nextWord != "FLAG_PORT") // On vérifie que le prochain mot est "FLAG_PORT", ce lexeme est automatiquement généré si un port a été déclaré
			{	
				m_msgBox.createMessage("203", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;
		}	
	
		else if (nbLexeme == 5) // CAS 5: FLAG_PORT correspondant à la déclaration d'un port
		{
			if (nextWord == ";")
			{	
				nbLexeme = 6;
			}
			else if (nextWord == ")")
			{
				nbLexeme = 7;
			}
			else 
			{
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
		}	
	
		else if (nbLexeme == 6) // CAS 6: Séparateur ";" permettant de reboucler sur un nouveau FLAG_PORT
		{
			if (nextWord != "FLAG_PORT")
			{
				m_msgBox.createMessage("203", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;
		}

		else if (nbLexeme == 7) // CAS 7: Paranthèse fermante ")"
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);	
				itr = m_listLexemes.end();
				itr--;	
			}
			nbLexeme = 8;

		}	

		else if (nbLexeme == 8) // CAS 8: Séparateur ";" 
		{
			if (nextWord != "end")
			{
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);	
				itr = m_listLexemes.end();
				itr--;	
			}
			nbLexeme = 9;
		}

		else if (nbLexeme == 9) // CAS 9: Mot clef "end"
		{
			if (nextWord != m_identifiant.m_word)
			{	
				m_msgBox.createMessage("201", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 10;
		}

		else if (nbLexeme == 10) // CAS 10: Mot clef "component"
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 11;
		}

		else if (nbLexeme == 11) // CAS 11: FIN DE LA VERIFICATION, séparateur ";" 
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("205", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}		
		count++;	
	}
	BlocNode::verifySyntax(); // En appelant cette fonction on va effectuer la vérification syntaxique des noeuds (ici seulement des ports) contenus par l'entité
}
