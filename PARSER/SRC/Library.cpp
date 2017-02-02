#include "../HEADER/Library.h"

/* 
##################Void VerifySyntax()##################
C'est la fonction qui gère la vérification de la syntaxe d'une librairie sur le principe d'une FSM.
Elle fonctionne avec une variable "nbLexeme" correspondant aux différents états de la FSM.
Dans chaque cas on vérifie le lexeme suivant:
	- s'il correspond à un cas normal, alors on passe à l'état souhaité
	- s'il n'est pas valide, alors on retourne une erreur et on coupe la vérification syntaxique
Comme dans une FSM il est possible de reboucler sur un même état, un état précédent ou un état suivant.
Chaque cas peut inclure plusieurs conditions et ainsi renvoyer vers différents états.

On notera que les FSM des classes qui ont des sous-branches (Entity, Architecture, Component, Process, InstructionIf et InstructionCase) utiliserons des flag pour identifier le noeud rencontré avoir d'avoir une structure bien imbriquée
 */

void Library::verifySyntax() 
{
	list <Lexeme>::iterator itr; //Création de l'itérateur permettant de parcourir chaque lexeme de la librairie
	int nbLexeme = 0; // nbLexeme correspond aux différents états de la FSM
	int count = 0; // Le compteur permet de relever le nombre de fois que l'on a changé d'étape

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++) //Début du parcours de la librairie pour vérification 
	{
		string monword = (*itr).m_word; // Déclaration de la variable qui contiendra le lexeme courant
		string nextWord = checkNextWord(count, itr); // Déclaration de la variable qui contiendra le mot suivant ou qui indiquera une erreur s'il n'y en a pas
	
		if (nbLexeme == 0) // CAS 0: library
		{
			nbLexeme = 1; 						
		}

		else if (nbLexeme == 1) // CAS 1: Etiquette de la librairie déclarée
		{
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord); // Une erreur s'affiche
				itr = m_listLexemes.end(); // On coupe la vérification
				itr--;
			}
			nbLexeme = 2;	
		}
		else if (nbLexeme == 2) // CAS 2: ";"
		{	
			if (nextWord != "use")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 3;		
		}	

		else if (nbLexeme == 3) // CAS 3: mot-clef use
		{
			if (nextWord != m_identifiant.m_word)
			{	
				m_msgBox.createMessage("201", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 4;
		}	
	
		else if (nbLexeme == 4) // CAS 4: Etiquette de la librairie voulue
		{
			if (nextWord != ".")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;
		}	
	
		else if (nbLexeme == 5) // CAS 5: "."
		{
			if (nextWord == "all") // Soit l'utilisateur souhaite utiliser tout le contenu de la librairie ou du package ...
			{	
				nbLexeme = 7; 
			}
			else if(verifyLabel(nextWord) == false) // Soit il souhaite aller à l'intérieur d'un package
			{
				nbLexeme = 6;
			}
			else
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}		
		}	
	
		else if (nbLexeme == 6) // CAS 6: Etiquette correspondant à un package de la librairie 
		{
			if (nextWord == ".") // Possibilité de reboucler sur le "." pour prendre tout le package ou un nouveau
			{
				nbLexeme = 5;
			}
			else if (nextWord == ";") // Possibilité d'aller directement au ";" s'il n'y a plus de package à récupérer 
			{
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 7) // CAS 7: mot-clef all
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 8;

		}	

		else if (nbLexeme == 8) // CAS 8: FIN DE LA VERIFICATION, séparateur ";"
		{
			
			if (nextWord == "use") // Possibilité d'avoir un nouveau "use" et donc de reboucler dans la "FSM"
			{				
				nbLexeme = 3;
			}
			else if (nextWord != "") // S'il n'y a pas de lexeme après le ";" alors la vérification syntaxique de la librairie est terminée
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;	
			}
		}
		count++; // Incrémentation du compteur	
	}
}
