#include "../HEADER/Process.h"

void Process::reorganizeLexemes()	//Reorganise les lexemes dans process
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

void Process::createVariable()		//Separe les lexemes des variables
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inVariable = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "variable")	//detecte le mot-clé variable
		{
			inVariable = true;
			itr++;
			m_listeBlocks.push_back(new Variable((*itr).m_word, (*itr).m_line, m_msgBox));
			m_msgBox.createMessage("811", (*itr).m_line, (*itr).m_word);	
			Lexeme flag("FLAG_VARI", (*itr).m_line);			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inVariable == true))	//Fin d'une variable avec le ";"
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inVariable = false;
		}
		else 
		{
			if (inVariable == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajoute les lexemes a la derniere variable créée
			}
			else
			{
				newList.push_back(*itr);	//Ajout des lexemes a la nouvelle liste
			}
		}	
	}
	m_listLexemes = newList;
}

void Process::createAssig()		//Separe les lexemes des assignations
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

void Process::createIfCase()		//Separe les lexemes des if et des case
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

/* 
##################Void verifySyntax()##################
Fonctionnement global expliqué dans Library.cpp
 */

void Process::verifySyntax() 
{	
	list <Lexeme>::iterator itr; 	// Création de l'itérateur permettant de parcourir chaque lexeme du signal
	int nbLexeme = 0; 		// nbLexeme correspond aux différents états de la FSM
	int count = 0; 			// Le compteur permet de relever le nombre de fois que l'on a changé d'étape
	
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++) //Début du parcours d'une entité pour vérification
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
	
		if (nbLexeme == 0) 	// CAS 0: Label correspondant à l'étiquette du process
		{
			if (nextWord != ":") // On s'assure que le prochain lexeme est bien ":"
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord); // Affiche une erreur
				itr = m_listLexemes.end(); // On coupe la vérification
				itr--;
			}
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)	// CAS 1: Séparateur ":"
		{
			if (nextWord != "process") 
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord); // Affiche une erreur
				itr = m_listLexemes.end(); // On coupe la vérification
				itr--;
			}
			nbLexeme = 2;				
		}	

		else if (nbLexeme == 2)	// CAS 2: Mot clef "process"
		{
			if (nextWord != "(")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;				
		}	

		else if (nbLexeme == 3)	// CAS 3: Paranthèse ouvrante "("
		{
			if (verifyLabel(nextWord) != false) // On s'assure que le prochain lexeme est un label valide
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;				
		}		

		else if (nbLexeme == 4) // CAS 4: Label correspondant à un paramètre de la liste de sensibilité
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
	
		else if (nbLexeme == 5) // CAS 5: Séparateur "," permettant de reboucler sur un autre paramètre de la liste de sensibilité
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;				
		}	

		else if (nbLexeme == 6) // CAS 6: Paranthèse fermante ")"
		{
			if (nextWord == "FLAG_VARI") 	// A cette endroit on ne peut avoir que des déclarations de variable
			{	
				nbLexeme = 7;
			}
			else if (nextWord == "begin")	// ou le mot clef "begin"
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

		else if (nbLexeme == 7) // CAS 7: FLAG_VARI correspondant à la déclaration d'un noeud variable
		{
			if (nextWord == "FLAG_VARI")	// On peut reboucler sur le même état si on a une autre déclaration de variable
			{	
				nbLexeme = 7;
			}
			else if (nextWord == "begin")	// ou aller à l'état "begin"
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

		else if (nbLexeme == 8) // CAS 8: Mot clef "begin"
		{
			if ((nextWord == "FLAG_IF") || (nextWord == "FLAG_CASE") || (nextWord == "FLAG_ASSIG")) // Après le begin on peut utiliser une structure if ou case, on peut aussi effectuer une assignation
			{	
				nbLexeme = 9;
			}
			else if (nextWord == "end")	// ou sortir du process via le mot clef "end"
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

		else if (nbLexeme == 9) // CAS 9: FLAG_IF, FLAG_CASE ou FLAG_ASSIG correspondant à l'utilisation d'un if, d'un case ou à une assignation
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

		else if (nbLexeme == 10) // CAS 10: Mot clef "end"
		{
			if (nextWord != "process")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 11;
		}

		else if (nbLexeme == 11) // CAS 11: Mot clef "process"
		{
			if (nextWord != m_identifiant.m_word)
			{	
				m_msgBox.createMessage("223", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 12;
		}

		else if (nbLexeme == 12) // CAS 12: Label correspondant à l'étiquette du process
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("225", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 13;
		}



		else if (nbLexeme == 13) // CAS 13: FIN DE LA VERIFICATION, séparateur ";" 
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
	BlocNode::verifySyntax(); // En appelant cette fonction on va effectuer la vérification syntaxique des noeuds (ici seulement des ports) contenus dans l'entity
}


