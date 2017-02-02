#include "../HEADER/Type.h"

/* 
##################Void VerifySyntax()##################
Fonctionnement global expliqué dans Library.cpp
 */

void Type::verifySyntax() 
{
	
	list <Lexeme>::iterator itr; //Création de l'itérateur permettant de parcourir chaque lexeme du signal
	int nbLexeme = 0; // nbLexeme correspond aux différents états de la FSM
	int count = 0; // Le compteur permet de relever le nombre de fois que l'on a changé d'étape
	/* Variables permettant de tester la cohérence d'un vecteur*/
	int nextNb = 0, prevNb = 0; 
	
/* Début du parcours de la déclaration d'un type pour vérification  */
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
	
		if (nbLexeme == 0) // CAS 0: Mot-clef "type" 
		{
			if(verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;			
		}

		else if (nbLexeme == 1) // CAS 1: Etiquette du type à déclarer
		{			
			if (nextWord != "is")
			{	
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;
		
		}

		else if (nbLexeme == 2) // CAS 2: Mot-clef "is"
		{	
			if (nextWord == "range") 	// Possibilité d'avoir le lexeme "range"
			{	
				nbLexeme = 3;
			}
			else if (nextWord == "array")	// ou array pour les composites
			{	
				nbLexeme = 7;
			}
			else if (nextWord == "(")	// ou une paranthèse pour les énumérés
			{	
				nbLexeme = 17;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

	/* Cas du type range */
		else if (nbLexeme == 3) // CAS 3: Utilisation du type "range"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str()); // On stocke la valeur du premier nombre sous forme d'entier
			nbLexeme = 4;
		}

		else if (nbLexeme == 4) // CAS 4: Première borne du range
		{
			if (nextWord != "to")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;
		}

		else if (nbLexeme == 5) // CAS 5: Cas unique du "To"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str()); // On stocke la valeur du second nombre sous forme d'entier
			if (nextNb <= prevNb)
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;
		}

		else if (nbLexeme == 6) // CAS 6: Seconde borne du range
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}		

	/* Cas d'un type composite (avec le mot-clef array) */
		else if (nbLexeme == 7) // CAS 7: Utilisation d'un type composite
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 8;
		}

		else if (nbLexeme == 8) // CAS 8: Paranthèse ouvrante "("
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str()); // On stocke la valeur du premier nombre sous forme d'entier
			nbLexeme = 9;
		}	

		else if (nbLexeme == 9) // CAS 9: Première borne du vecteur
		{
			if (nextWord == "downto")
			{
				nbLexeme = 10;
			}
			else if (nextWord == "to")
			{
				nbLexeme = 11;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 10) // CAS 10: Traitement du cas "downto"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str()); // On stocke la valeur du second nombre sous forme d'entier
			if (nextNb >= prevNb)
			{
				m_msgBox.createMessage("210", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 12;
		}

		else if (nbLexeme == 11) // CAS 11: Traitement du cas "to"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str()); // On stocke la valeur du second nombre sous forme d'entier
			if (nextNb <= prevNb)
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 12;
		}

		else if (nbLexeme == 12) // CAS 12: Seconde borne du vecteur
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 13;
		}

		else if (nbLexeme == 13) // CAS 13: paranthèse fermante ")"
		{
			if (nextWord != "of")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 14;
		}	

		else if (nbLexeme == 14) // CAS 14: Mot-clef "of"
		{
			if (verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 15;
		}	

		else if (nbLexeme == 15) // CAS 15: Etiquette qui doit correspondre à celle d'un type déclaré au préalable
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}


	/* Cas d'un type énuméré (avec paranthèse ouvrante) */ 
		else if (nbLexeme == 17) // CAS 17: Paranthèse ouvrante "("
		{
			if (nextWord == "\'")
			{	
				nbLexeme = 20;
			}
			else if (nextWord == "\"" )
			{	
				nbLexeme = 24;
			}
			else if (verifyLabel(nextWord) == false)
			{
				nbLexeme = 18;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}
		
		// Cas d'un simple étiquette 
		else if (nbLexeme == 18) // CAS 18: Utilisation d'étiquettes
		{
			if (nextWord == ",")
			{
				nbLexeme = 19;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 28;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 19) // CAS 19: Séparateur "," permettant de reboucler sur une autre étiquette
		{
			if (verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 18;
		}	

		// Cas d'un type composé de simples caractères
		else if (nbLexeme == 20) // CAS 20: Premier caractère "'" permettant d'encadrer un char (un lexeme de taille 1)
		{
			if (((nextWord == "-") || (verifyGlobalWord(nextWord) == false)) && (nextWord.size() == 1))
			{
				nbLexeme = 21;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}	

		else if (nbLexeme == 21) // CAS 21: Caractère alphanumérique
		{
			if (nextWord != "\'")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;
		}

		else if (nbLexeme == 22) // CAS 22: Second caractère "'" permettant d'encadrer un char (un lexeme de taille 1)
		{
			if (nextWord == ",")
			{
				nbLexeme = 23;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 28;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 23) // CAS 23: Séparateur "," permettant de reboucler sur d'autres caractères
		{
			if (nextWord != "\'")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 20;
		}	

		// Cas d'une suite de bits encadrée par deux guillemets "bits"

		else if (nbLexeme == 24) // CAS 24: Ici on doit avoir une première guillemet pour encadrer le vecteur 
		{
			if ( nextWord.size() > 1) // On doit avoir au moins 2 caractères pour avoir un vecteur
			{
				for (int i=0; i < nextWord.size(); i++)
				{
					if ((nextWord[i] != '0') && (nextWord[i] != '1')) // Le type bit_vector sous-entend qu'il faut des bits (1 ou 0)
					{	
						m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
						itr = m_listLexemes.end();
						itr--;
						i = nextWord.size();	// On sort de la condition
					}
				}
			}

			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 25;
		}

		else if (nbLexeme == 25) //CAS 25: C'est ici que l'on doit avoir le vecteur de bits
		{
			if (nextWord != "\"")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 26;
		}

		else if (nbLexeme == 26) // CAS 26: Ici on doit avoir une seconde guillemet pour encadrer le vecteur 
		{
			if (nextWord == ",")
			{
				nbLexeme = 27;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 28;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 27) // CAS 27: Séparateur "," pour reboucler sur un autre vecteur
		{
			if (nextWord != "\"")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 24;
		}

		else if (nbLexeme == 28) // CAS 28: Paranthèse fermante ")" pour clôturer le type énuméré
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}

		else if (nbLexeme == 16) // CAS 16: FIN DE LA VERIFICATION, séparateur ";"
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("213", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}	
		count++;
	}
}
