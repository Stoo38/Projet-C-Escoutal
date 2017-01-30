#include "../HEADER/Type.h"

void Type::verifySyntax() 
{
	
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);

		cout << count << " " << m_listLexemes.size() << " " << nbLexeme << " " << monword << " " << nextWord <<  endl;
	
		if (nbLexeme == 0)
		{
			nbLexeme = 1;				
		}

		else if (nbLexeme == 1)
		{
			
			if (nextWord != "is")
			{	
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;
		
		}

		else if (nbLexeme == 2)
		{	
			if (nextWord == "port")
			{	
				nbLexeme = 3;
			}
			else if (nextWord == "end")
			{	
				nbLexeme = 9;
			}
			else
			{
				m_msgBox.createMessage("206", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
					
		}		
		count++;	
	}
}
