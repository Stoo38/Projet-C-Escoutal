#include "../HEADER/Type.h"

void Type::verifySyntax() 
{
	
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	int nextNb=0, prevNb=0;
	

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);

		cout << count << " " << m_listLexemes.size() << " " << nbLexeme << " " << monword << " " << nextWord <<  endl;
	
		if (nbLexeme == 0)
		{
			if(verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;			
		}

		else if (nbLexeme == 1)
		{			
			if (nextWord != "is")
			{	
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 2;
		
		}

		else if (nbLexeme == 2)
		{	
			if (nextWord == "range")
			{	
				nbLexeme = 3;
			}
			else if (nextWord == "array")
			{	
				nbLexeme = 7;
			}
			else if (nextWord == "(")
			{	
				nbLexeme = 17;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 3)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str());
			//cout << "PREVIOUS NUMBER" << prevNb << endl;
			nbLexeme = 4;
		}

		else if (nbLexeme == 4)
		{
			if (nextWord != "to")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 5;
		}

		else if (nbLexeme == 5)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			//cout << "NEXT NUMBER" << prevNb << endl;
			if (nextNb <= prevNb)
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;
		}

		else if (nbLexeme == 6)
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}		

		else if (nbLexeme == 7)
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 8;
		}

		else if (nbLexeme == 8)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str());
			//cout << "PREVIOUS NUMBER" << prevNb << endl;
			nbLexeme = 9;
		}	

		else if (nbLexeme == 9)
		{
			if (nextWord == "downto")
			{
				nbLexeme = 10;
			}
			else if (nextWord == "to")
			{
				nbLexeme = 16;
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 10)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			cout << "NEXT NUMBER" << prevNb << endl;
			if (nextNb >= prevNb)
			{
				m_msgBox.createMessage("210", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;
		}

		else if (nbLexeme == 16)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			//cout << "NEXT NUMBER" << prevNb << endl;
			if (nextNb <= prevNb)
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;
		}

		else if (nbLexeme == 9)
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 10;
		}		
			












		else if (nbLexeme == 16)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("213", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}


	
		count++;	
	}
}
