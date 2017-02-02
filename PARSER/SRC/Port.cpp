#include "../HEADER/Port.h"

void Port::reorganizeLexemes()
{
	m_listLexemes.pop_front();
}


/* 
##################Void VerifySyntax()##################
Fonctionnement global expliqué dans Library.cpp
 */

void Port::verifySyntax() 
{
	list <Lexeme>::iterator itr; 	// Création de l'itérateur permettant de parcourir chaque lexeme du signal
	int nbLexeme = 0; 		// nbLexeme correspond aux différents états de la FSM
	int count = 0; 			// Le compteur permet de relever le nombre de fois que l'on a changé d'étape
	/* Variables permettant de tester la cohérence d'un vecteur*/
	int nextNb = 0, prevNb = 0;  

	/* Tableau contenant les différents types pris en compte par le compilateur */
	string myTypes[7];
	myTypes[0] = "std_logic";
	myTypes[1] = "std_ulogic";
	myTypes[2] = "bit";
	myTypes[3] = "std_logic_vector";
	myTypes[4] = "std_ulogic_vector";
	myTypes[5] = "bit_vector";
	myTypes[6] = "integer";

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++) //Début du parcours d'un port pour vérification
	{
		string monword = (*itr).m_word; 		// Déclaration de la variable qui contiendra le lexeme courant
		string nextWord = checkNextWord(count, itr); 	// Déclaration de la variable qui contiendra le mot suivant ou qui indiquera une erreur s'il n'y en a pas

		if (nbLexeme == 0)     // CAS 0: Label correspondant au nom du port
		{	
			if (nextWord == ",")
			{
				nbLexeme = 1;
			}
			else if (nextWord == ":")
			{
				nbLexeme = 2;
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}						
		}

		else if (nbLexeme == 1) // CAS 1: Séparateur "," permettant d'avoir plusieurs ports sur une même ligne
		{
			if(verifyLabel(nextWord) != false) // On vérifie que l'étiquette du port est valide
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord); // On afficher une erreur 
				itr = m_listLexemes.end(); // On coupe la vérification
				itr--;
			}
			nbLexeme = 0;
		}

		else if (nbLexeme == 2) // CAS 2: Séparateur ":" 
		{	
			if (nextWord == "in") 		// On distingue le "in" et le "out" pour stocker cette information
			{	
				nbLexeme = 3;	
				m_in = true;		// Si on a un "in" le flag passe à true
			}
			else if(nextWord == "out")
			{
				nbLexeme = 3;		// Si c'est un "out" il reste à false
				m_in = false;
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}		
		}	

		else if (nbLexeme == 3) // CAS 3: Mot clef "in" ou "out"
		{
			bool flag = false;	//Si on a un type valide le flag passera à true
			for (int i = 0; i < 7; i++)	// On parcourt le tableau afin d'identifier le type 
			{
				// Cas où l'on a un type simple
				if ((nextWord == myTypes[i]) && (i < 3)) // Les premiers éléments du tableau correspondent aux types simples
				{
					flag = true;
					nbLexeme = 4;
					i = 7; //fin de boucle
					m_type = nextWord;	// On stocke le type du port
					
				}
				//Cas où l'on a un type vector
				else if ((nextWord == myTypes[i]) && (i >= 3) && (i < 6)) // Après les types simples on trouve les types vector dans le tableau
				{
					flag = true;
					nbLexeme = 5;		
					i = 7; //fin de boucle
					m_type = nextWord;	// On stocke le type du port
				}
				//Cas où l'on a un type range
				else if (nextWord == myTypes[i]) // Dernier type possible dans le tableau
				{
					flag = true;
					nbLexeme = 11;
					i = 7; //fin de boucle
					m_type = nextWord;	// On stocke le type du port
				}
			}
			if (flag == false)
			{
				m_msgBox.createMessage("208", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}	
		}	
		//TYPE SIMPLE
		else if (nbLexeme == 4) // CAS 4: Type simple tel que bit ou std_logic
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
			/* Le type étant simple, la taille est unitaire */
			m_size_a = 0; 
			m_size_b = 0;
			itr = m_listLexemes.end();
			itr--;
		}
	
		//TYPE VECTOR
		else if (nbLexeme == 5) // CAS 5: Type vecteur tel que bit_vector ou std_logic_vector
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;
		}	

		else if (nbLexeme == 6) // CAS 6: Paranthèse ouvrante "("
		{
			if (verifyNumber(nextWord) != false) // On vérifie bien que le prochain lexeme est un nombre
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str()); // On stocke la valeur du premier nombre sous forme d'entier
			m_size_a = prevNb; // On stocke la borne
			nbLexeme = 7;
		}	

		else if (nbLexeme == 7) // CAS 7: Premier nombre permettant de dimensionner le vecteur
		{
			if (nextWord == "downto")	// On distingue le "downto"
			{
				nbLexeme = 8;
			}
			else if (nextWord == "to")	// du "to"
			{
				nbLexeme = 16;
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 8) // CAS 8: Mot clef "downto"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str()); // On stocke la valeur du second nombre sous forme d'entier
			m_size_b = nextNb; 		 // On stocke la seconde borne
			if (nextNb >= prevNb)		 // Pour un downto le premier nombre doit être supérieur au second
			{
				m_msgBox.createMessage("210", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;
		}

		else if (nbLexeme == 16) // CAS 16: Mot clef "to"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			if (nextNb <= prevNb) // Pour un to le premier nombre doit être inférieur au second
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;
		}

		else if (nbLexeme == 9) // CAS 9: Second nombre permettant de dimensionner le vecteur
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 10;
		}

		else if (nbLexeme == 10) // CAS 10: Paranthèse fermante ")"
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}
		
		// TYPE  RANGE
		else if (nbLexeme == 11) // CAS 11: Type range
		{
			if (nextWord != "range")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 12;
		}

		else if (nbLexeme == 12) // CAS 12: Mot clef "range"
		{
			if (verifyNumber(nextWord) != false) // On vérifie bien que le prochain lexeme est un nombre
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str());
			nbLexeme = 13;
		}

		else if (nbLexeme == 13) // CAS 13: Première borne de la plage de valeur du range
		{
			if (nextWord != "to")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 14;
		}

		else if (nbLexeme == 14) // CAS 14: Mot  clef "to"
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			if (nextNb <= prevNb)
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 15;
		}

		else if (nbLexeme == 15) // CAS 15: Seconde borne de la plage de valeur du range
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}

		count++; // Incrémentation du compteur	
	}
}
