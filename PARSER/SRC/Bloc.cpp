#include "../HEADER/Bloc.h"

using namespace std;

//ACCESSEURS
const string & Bloc::getIdentifiant() const		//Renvoie l'identifiant
{
	return m_identifiant.m_word;
}

const string Bloc::getKeyWord() const			//Renvoie le mot-clé de la classe
{
	return m_keyword.m_word;
}

//MODIFIEURS
void Bloc::addLexeme(string lexeme, int nLine)		//Permet d'ajouter un Lexeme à la liste
{
	Lexeme newLexeme(lexeme, nLine);
	m_listLexemes.push_back(newLexeme);
}

void Bloc::displayLexemes()				//Permet d'afficher tous les lexemes contenus dans la liste
{
	cout << "List of lexemes contained in the block " << getKeyWord() << " " << getIdentifiant() << endl;
	list <Lexeme>::iterator itr;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		cout << (*itr).m_line << " " << (*itr).m_word << endl;		 
	}
}

int Bloc::trySpecialCharacter(Lexeme lex)		//Permet de voir s'il y a des caracteres speciaux dans le lexeme
{							//Parcourt pour cela tous les autres caracteres valides
	string word = lex.m_word;
	if(word.size() == 1)
	{
		for(char i = 33; i < 127; i++)
		{
			if(word[0] == i)
			{
				return 1;
			}	
			if (i == 47)
			{
				i = 57;
			}
			if (i == 64)
			{
				i = 90;
			}
			if (i == 94)
			{
				i = 95;
			}
			if (i == 96)
			{
				i = 122;
			}
		}
	}
	return 0;		
}

bool Bloc::verifyFirstCharacter(Lexeme lex)		//Verifie que le premier caractere est une lettre
{
	string word = lex.m_word;
	bool error = true;
	if (trySpecialCharacter(lex) != 1)
	{
		for (char i = 97; i < 123; i++)
		{
			if(word[0] == i)
			{
				error = false;
			}
		}
	}
	if (error == true)
	{
		m_msgBox.createMessage("006", lex.m_line, lex.m_word);
	}
	return error;
}

bool Bloc::verifyUnderscore(Lexeme lex)			//Verifie que le premier et le dernier caractere du lexeme n'est pas un underscore
{
	string word = lex.m_word;
	bool error = false;
	if ((word[word.size()-1] == 95) || (word[0] == 95)) 
	{
		m_msgBox.createMessage("007", lex.m_line, lex.m_word);
		error = true;
	}
	return error;
}

bool Bloc::verifyGlobalWord(Lexeme lex)			//Verifie que le lexeme n'est compose que de lettres, chiffres et underscore
{
	string word = lex.m_word;
	bool error;
	for (int i = 0; i < word.size(); i++)
	{		
		error = true;
		for (char j = 48; j < 123; j++)
		{
			if(word[i] == j)
			{
				error = false;
				j = 123;
			}
			if (j == 57)
			{
				j = 94;
			}
			if (j == 95)
			{
				j++;
			}
		}
		if (error == true)
		{
			m_msgBox.createMessage("008", lex.m_line, lex.m_word);
		}
	}
	return error;
}

bool Bloc::verifyLabel(Lexeme lex)		//Lance toutes les fonctions pour verifier que le lexeme est une etiquette valide
{
	bool error1, error2, error3, error4;
	error1 = verifyGlobalWord(lex);	
	error2 = verifyUnderscore(lex);
	error3 = verifyFirstCharacter(lex);
	error4 = compareKeyWords(lex);
	if ((error1 == true)||(error2 == true)||(error3 == true)||(error4 == true))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Bloc::compareKeyWords(Lexeme lex)		//Compare les lexemes aux mot-cles contenus dans le fichier kaywords.txt
{
		
	bool error = false;		
	ifstream myFile("PARSER/keywords.txt"); 
	if(myFile)					
	{		
		string line;	
		vector<string> list_keywords;
		while(getline(myFile, line))					
		{
			line = eraseComment(line);	
			list_keywords.push_back(line);	
			list_keywords = eraseSpace(list_keywords);

		}
		vector<string>::iterator it;
		for(it=list_keywords.begin(); it != list_keywords.end(); it++)
		{
			if (lex.m_word == *it)
			{
				m_msgBox.createMessage("028", lex.m_line, lex.m_word);
				error = true;
			}
		}							
	}
	else
	{
		m_msgBox.createMessage("025", 0, "keywords.txt");		
	}	
	return error;
}

string Bloc::checkNextWord(int count, list<Lexeme>::iterator itr)	//Renvoie le prochain mot quand on parcourt la liste de lexemes
{
	if (count == (m_listLexemes.size()-1))
	{	
		return "";		
	}
	
	else 
	{
		list<Lexeme>::iterator itr2;
		itr2 = itr;
		itr2++;

		return (*itr2).m_word;
	}
}

bool Bloc::verifyNumber(string word)					//Verifie que le lexeme est un nombre
{
	bool error = true;
	for (char j = 45; j < 58; j++)					//verifie si le premier caractere est "-" et donc si le nombre est negatif
	{
		if (word[0] == j)
		{
			error = false;
			j = 58;
		}
		if (j == 45)
		{
			j = 47;
		}
	}
	if ((error)||(word.size() == 1))
	{
		return error;
	}
	
	for (int i = 1; i < word.size(); i++)
	{	
		error = true;	
		for (char j = 48; j < 58; j++)
		{
			if(word[i] == j)
			{
				error = false;
				j = 58;
			}
		}
		if (error)
		{
			return error;
		}
	}
	return error;
}

