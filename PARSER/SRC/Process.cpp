#include "../HEADER/Process.h"

const string Process::getNameBlock() const
{
	return "okok";
}

void Process::reorganizeLexemes()
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
	
	if ((m_listLexemes.front()).m_word == ":")
	{
		m_listLexemes.pop_front();
	}
		
	Lexeme n1(":", m_identifiant.m_line);
	Lexeme n2("process", m_identifiant.m_line);
	m_listLexemes.push_front(n2);
	m_listLexemes.push_front(n1);	
	m_listLexemes.push_front(m_identifiant);
}
