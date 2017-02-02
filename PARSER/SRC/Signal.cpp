#include "../HEADER/Signal.h"

/* 
##################Void VerifySyntax()##################
Fonctionnement global expliqué dans Library.cpp
 */

void Signal::verifySyntax() 
{
	list <Lexeme>::iterator itr; 	// Création de l'itérateur permettant de parcourir chaque lexeme du signal
	int nbLexeme = 0; 		// nbLexeme correspond aux différents états de la FSM
	int count = 0; 			// Le compteur permet de relever le nombre de fois que l'on a changé d'étape
	/* Variables permettant de tester la cohérence d'un vecteur*/
	int nextNb = 0, prevNb = 0; 
	int sizeVector = 0; 

	/* Tableau contenant les différents types pris en compte par le compilateur */
	string myTypes[3];
	myTypes[0] = "bit";
	myTypes[1] = "bit_vector";
	myTypes[2] = "unsigned";

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++) //Début du parcours d'un signal pour vérification 
	{
		string monword = (*itr).m_word; 		// Déclaration de la variable qui contiendra le lexeme courant
		string nextWord = checkNextWord(count, itr); 	// Déclaration de la variable qui contiendra le mot suivant ou qui indiquera une erreur s'il n'y en a pas

	
		if (nbLexeme == 0) 	// CAS 0: Mot-clef "signal" 
		{	
			if(verifyLabel(nextWord) != false) 	// Ici on utilise la fonction verifyLabel pour vérifier que le prochain lexeme est valide
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord); // Affiche une erreur
				itr = m_listLexemes.end(); // On coupe la vérification
				itr--;
			}
			nbLexeme = 1;						
		}

		else if (nbLexeme == 1)	 // CAS 1: Etiquette du signal à déclarer
		{
			if (nextWord == ",") 	  // Possibilité d'avoir une "," comme prochain lexeme
			{
				nbLexeme = 2;
			}
			else if (nextWord == ":") // ou ":"
			{
				nbLexeme = 3;
			}
			else
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 2)	// CAS 2: Séparateur "," autorisant la déclaration, de plusieurs signaux
		{	
			if(verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;		
		}	

		else if (nbLexeme == 3) // CAS 3: Séparateur ":" - vérification du type 
		{
			bool flag = false;
			for (int i = 0; i < 3; i++)
			{
				if ((nextWord == myTypes[i]) && (i < 1))
				{
					//ici ce sont les cas simples
					flag = true;
					nbLexeme = 4;
					i = 3; 		//fin de boucle
					
				}
				else if (nextWord == myTypes[i])
				{
					//ici ce sont les cas type vector/unsigned
					flag = true;
					nbLexeme = 10;		
					i = 3; 		//fin de boucle
				}
			}

			if (flag == false)
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}	
		}	
		//TYPE SIMPLE
		else if (nbLexeme == 4) // CAS 4: Utilisation d'un type "simple" tel que "bit"
		{
			if (nextWord == ";") 		// Possibilité que le prochain lexeme soit un ";"
			{
				nbLexeme = 22;
			}
			else if (nextWord == "<") 	// ou un "<"
			{
				nbLexeme = 5;
			}
			else
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 5) // CAS 5: Lexeme "<" à combiner avec "=" pour effectuer l'affectation d'un signal
		{	
			if(nextWord != "=")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;		
		}	

		else if (nbLexeme == 6) // CAS 6: Lexeme "=" permettant d'assurer l'affectation
		{	
			if(nextWord != "\'")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 7;		
		}	

		else if (nbLexeme == 7) // CAS 7: Premier caractère "'" permettant d'encadrer un char (un lexeme de taille 1 pouvant être 0 ou 1 pour le type bit)
		{	
			if((nextWord.size() == 1) &&  ((nextWord[0] == '0') || (nextWord[0] == '1')))  // On teste si on a bien un caractère, et si c'est bien un bit
			{
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}					
		}

		else if (nbLexeme == 8) // CAS 8: Ici on doit avoir un bit (0 ou 1) dans le cas du type "bit"
		{	
			if(nextWord != "\'") 
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;		
		}

		else if (nbLexeme == 9) // CAS 9: Second caractère "'" permettant d'encadrer un char (un lexeme de taille 1 pouvant être 0 ou 1 pour le type bit)
		{	
			if(nextWord != ";")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;		
		}


	
		//TYPE VECTOR ET UNSIGNED
		else if (nbLexeme == 10) // CAS 10: Utilisation d'un type vector ou unsigned
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 11;
		}

		else if (nbLexeme == 11) // CAS 11: Paranthèse ouvrante "("
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str()); // On stocke la valeur du premier nombre sous forme d'entier
			nbLexeme = 12;
		}	

		else if (nbLexeme == 12) // CAS 12: Première borne du vecteur
		{
			if (nextWord == "downto")	// On peut avoir un "downto"
			{
				nbLexeme = 13;
			}
			else if (nextWord == "to")  	// ou un "to"
			{
				nbLexeme = 14;
			}
			else
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 13) // CAS 13: Traitement du cas Downto
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str()); // On stocke la valeur du second nombre sous forme d'entier
			if (nextNb >= prevNb) // Pour un downto le premier nombre doit être supérieur au second
			{
				m_msgBox.createMessage("210", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			sizeVector = (prevNb - nextNb); // On calcule la taille du vecteur
			nbLexeme = 15;
		}

		else if (nbLexeme == 14) // CAS 14: Traitement du cas To
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
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
			sizeVector = (nextNb - prevNb);
			nbLexeme = 15;
		}

		else if (nbLexeme == 15) // CAS 15: Seconde borne du vecteur qui doit être supérieure à la première en cas de "to" et inférieure en cas de "downto"
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}	

		else if (nbLexeme == 16) // CAS 16: Paranthèse fermante ")"
		{
			if (nextWord == ";")
			{
				nbLexeme = 22;
			}
			else if (nextWord == "<")
			{
				nbLexeme = 17;
			}
			else
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 17) // CAS 17: Lexeme "<" à combiner avec "=" pour effectuer une affectation
		{	
			if(nextWord != "=")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 18;		
		}	

		else if (nbLexeme == 18) // CAS 18: Lexeme "=" permettant d'assurer l'affectation
		{	
			if(nextWord != "\"")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 19;		
		}	

		else if (nbLexeme == 19) // CAS 19: Premier caractère """ permettant d'encadrer un vecteur (un lexeme de la taille du vecteur défini auparavant)
		{	
			if ( nextWord.size() == (sizeVector+1))		// On va chercher que le vecteur de bits déclaré est de la même taille que celle déclarée auparavant
			{
				for (int i=0; i < nextWord.size(); i++)	// Parcours des caractères du lexeme
				{
					if ((nextWord[i] != '0') && (nextWord[i] != '1')) // Chaque caractère doit être un bit
					{	
						m_msgBox.createMessage("216", (*itr).m_line, nextWord);		
						itr = m_listLexemes.end();
						itr--;
						i = nextWord.size();
					}
				}
			}

			else
			{
				m_msgBox.createMessage("218", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 20;					
		}

		else if (nbLexeme == 20) // CAS 20: Vecteur de bits dont la taille a été définie auparavant
		{	
			if(nextWord != "\"")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 21;		
		}

		else if (nbLexeme == 21) // CAS 21: Second caractère """ permettant d'encadrer un vecteur (un lexeme de la taille du vecteur défini auparavant)
		{	
			if(nextWord != ";")
			{
				m_msgBox.createMessage("216", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;		
		}


		else if (nbLexeme == 22) // CAS 22: FIN DE LA VERIFICATION, séparateur ";"
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("217", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}
		count++; // Incrémentation du compteur
	}
}
