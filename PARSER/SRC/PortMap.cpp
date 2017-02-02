#include "../HEADER/PortMap.h"

void PortMap::reorganizeLexemes()
{
	m_listLexemes.pop_front();
}


/* 
##################Void verifySyntax()##################
Fonctionnement global expliqué dans Library.cpp
 */

void PortMap::verifySyntax()
{
	list <Lexeme>::iterator itr; 	// Création de l'itérateur permettant de parcourir chaque lexeme du signal
	int nbLexeme = 0; 		// nbLexeme correspond aux différents états de la FSM
	int count = 0; 			// Le compteur permet de relever le nombre de fois que l'on a changé d'étape
	
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++) //Début du parcours d'une entité pour vérification
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
	
		if (nbLexeme == 0) 	// CAS 0: Label correspondant à l'étiquette du port map
		{
			if (nextWord != ":") // Le prochain lexeme doit être un ":"
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord); // Affiche une erreur
				itr = m_listLexemes.end(); // On coupe la vérification
				itr--;
			}
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)	// CAS 1: Séparateur ":"
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;				
		}

		else if (nbLexeme == 2) // CAS 2: Label correspondant à l'étiquette d'un component
		{
			if (nextWord != "port")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;				
		}

		else if (nbLexeme == 3) // CAS 3: Mot clef "port"
		{
			if (nextWord != "map")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;			
		}

		else if (nbLexeme == 4) // CAS 4: Mot clef "map"
		{
			if (nextWord != "(")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;				
		}

		else if (nbLexeme == 5) // CAS 5: Paranthèse ouvrante "("
		{
			if (verifyLabel(nextWord) != false) // On vérifie que le label à venir est valide
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;				
		}

		else if (nbLexeme == 6) // CAS 6: Label correspondant à un signal à mapper
		{	
			if (nextWord == ",") 		// Le prochain lexeme peut être une ","
			{	
				nbLexeme = 7;
			}
			else if (nextWord == ")")	// ou une ")"
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

		else if (nbLexeme == 7) // CAS 7: Séparateur ","
		{
			if (verifyLabel(nextWord) != false)
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
			nbLexeme = 6;			
		}

		else if (nbLexeme == 8) // CAS 8: Paranthèse fermante ")"
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("221", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;			
			}
			nbLexeme = 9;			
		}	

		else if (nbLexeme == 9) // CAS 9: FIN DE LA VERIFICATION, séparateur ";" 
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("222", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}		
		count++; // Incrémentation du compteur
	}
}
