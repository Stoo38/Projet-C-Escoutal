#include "../HEADER/Library.h"

using namespace std;

void Library::verifySyntax() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
		cout << nbLexeme << " " << count << " " << m_listLexemes.size() << endl;
		cout << monword << " " << nextWord << endl;

	
		if (nbLexeme == 0)
		{
			nbLexeme = 1;							
		}

		else if (nbLexeme == 1)
		{
			
<<<<<<< HEAD
			if (checkNextWord(count, itr) == "use")
			{
				cout << "OKOKOKOKOKn°1" << endl;	
			}
			else
			{
				m_msgBox.createMessage("072", (*itr).m_line, (*itr).m_word);
			}
			
=======
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
			}
>>>>>>> a98a880e59749bcab0ea055557260e902c45a27f
			nbLexeme = 2;
		
		}

		else if (nbLexeme == 2)
		{	
			if (nextWord != "use")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
			}
			nbLexeme = 3;		
		}	

		else if (nbLexeme == 3)
		{
			if (nextWord != m_identifiant.m_word)
			{	
				m_msgBox.createMessage("201", (*itr).m_line, nextWord);
			}
			nbLexeme = 4;
		}	
	
		else if (nbLexeme == 4)
		{
			if (nextWord != ".")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
			}
			nbLexeme = 5;
		}	
	
		else if (nbLexeme == 5)
		{
			if (nextWord == "all")
			{	
				nbLexeme = 7;
			}
			else
			{
				verifyLabel(nextWord);
				nbLexeme = 6;
			}
			

/*
			if (monword == ".")
			{
				if (checkNextWord(count, itr) == "all")
				{
					cout << "OKOKOKOKOKn°5" << endl;
					cout << "Next word: " << checkNextWord(count, itr) << endl;
					nbLexeme = 7;
				}
				else
				{
					cout << "OKOKOKOKOKn°5" << endl;
					cout << "Next word: " << checkNextWord(count, itr) << endl;
					nbLexeme = 6;
				}
			}
			else
			{
				cout << "NONONO" << endl;
			}*/
		}	
	
		else if (nbLexeme == 6)
		{
			if (nextWord == ".")
			{
				nbLexeme = 5;
			}
			else if (nextWord == ";")
			{

				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
			}
		}

		else if (nbLexeme == 7)
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);		
			}
			nbLexeme = 8;

		}	

		else if (nbLexeme == 8)
		{
			
			if (nextWord == "use")
			{
				
				nbLexeme = 3;
			}
			else if (nextWord == "")
			{
				cout << "error" << endl;	
			}	
			else
			{
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				//itr--;
			}
		}

		count++;	
	}
}
