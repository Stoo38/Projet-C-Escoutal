#include "../HEADER/InstructionAssig.h"

void InstructionAssig::reorganizeLexemes()		//Reorganise les lexemes contenus dans l'assignation d'un signal
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	BlocNode::reorganizeLexemes();
}
