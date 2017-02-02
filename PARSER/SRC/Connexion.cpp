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
			(m_gate.m_listLexemes).push_back(*itr);
		}
		else
		{
			newList.push_back(*itr);
		}
	}
	m_listLexemes = newList;
}
