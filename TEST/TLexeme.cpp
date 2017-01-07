#include "../PARSER/HEADER/Lexeme.h"
#include <list>

using namespace std;

int main()
{
	Lexeme mot("Hello", 10);
	cout << "Test avec la classe Lexeme directement:" << endl;
	cout << mot.m_word << endl;
	cout << mot.m_line << endl;
	
	list<Lexeme> listLexemes;
	listLexemes.push_back(mot);
	list<Lexeme>::iterator it;
	cout << "Test avec la classe Lexeme stockée dans une liste:" << endl;
	for(it = listLexemes.begin(); it != listLexemes.end(); it++)
	{
		cout << (*it).m_word << endl;
		cout << (*it).m_line << endl;
	}	
}
