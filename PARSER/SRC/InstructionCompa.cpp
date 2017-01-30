#include "../HEADER/InstructionCompa.h"

void InstructionCompa::reorganizeLexemes()
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	BlocNode::reorganizeLexemes();
}
