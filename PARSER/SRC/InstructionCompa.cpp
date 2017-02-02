#include "../HEADER/InstructionCompa.h"

void InstructionCompa::reorganizeLexemes()	//Reorganise les lexemes contenus dans la comparaison des if
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	BlocNode::reorganizeLexemes();
}
