#include "../HEADER/InstructionAssig.h"

/*void InstructionAssig::reorganizeLexemes();
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	BlocNode::reorganizeLexemes();
}*/

void InstructionAssig::reorganizeLexemes()
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	BlocNode::reorganizeLexemes();
}
