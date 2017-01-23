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
<<<<<<< HEAD
		cout << count << " " << m_listLexemes.size() << " " << nbLexeme << " " << monword << " " << nextWord <<  endl;
=======
		cout << nbLexeme << " " << count << " " << m_listLexemes.size() << endl;
		cout << monword << " " << nextWord << endl;
>>>>>>> a98a880e59749bcab0ea055557260e902c45a27f

	
		if (nbLexeme == 0)
		{
			nbLexeme = 1;							
		}

		else if (nbLexeme == 1)
		{
			
			if (nextWord != ";")
			{	
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
			}
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
				itr--;
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
<<<<<<< HEAD
			
=======
				cout << "error" << endl;	
>>>>>>> a98a880e59749bcab0ea055557260e902c45a27f
			}	
			else
			{				
				m_msgBox.createMessage("202", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
<<<<<<< HEAD
				itr--;
=======
				//itr--;
>>>>>>> a98a880e59749bcab0ea055557260e902c45a27f
			}
			
		}

		count++;	
	}
}
