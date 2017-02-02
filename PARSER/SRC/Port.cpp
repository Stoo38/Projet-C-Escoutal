#include "../HEADER/Port.h"

void Port::reorganizeLexemes()
{
	m_listLexemes.pop_front();
}


void Port::verifySyntax() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	int nextNb=0, prevNb=0;

	string myTypes[7];
	myTypes[0] = "std_logic";
	myTypes[1] = "std_ulogic";
	myTypes[2] = "bit";
	myTypes[3] = "std_logic_vector";
	myTypes[4] = "std_ulogic_vector";
	myTypes[5] = "bit_vector";
	myTypes[6] = "integer";

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);
	
		if (nbLexeme == 0)
		{	
			if (nextWord == ",")
			{
				nbLexeme = 1;
			}
			else if (nextWord == ":")
			{
				nbLexeme = 2;
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}						
		}

		else if (nbLexeme == 1)
		{
			if(verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 0;
		}

		else if (nbLexeme == 2)
		{	
			if (nextWord == "in")
			{	
				nbLexeme = 3;	
				m_in = true;
			}
			else if(nextWord == "out")
			{
				nbLexeme = 3;
				m_in = false;
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}		
		}	

		else if (nbLexeme == 3)
		{
			bool flag = false;
			for (int i = 0; i < 7; i++)
			{
				if ((nextWord == myTypes[i]) && (i < 3))
				{
					//ici c'est les cas simples
					flag = true;
					nbLexeme = 4;
					i = 7; //fin de boucle
					m_type = nextWord;
					
				}
				else if ((nextWord == myTypes[i]) && (i >= 3) && (i < 6))
				{
					//ici c'est les cas type vector
					flag = true;
					nbLexeme = 5;		
					i = 7; //fin de boucle
					m_type = nextWord;
				}
				else if (nextWord == myTypes[i])
				{
					//ici c'est les cas type range	
					flag = true;
					nbLexeme = 11;
					i = 7; //fin de boucle
					m_type = nextWord;
				}
			}
			if (flag == false)
			{
				m_msgBox.createMessage("208", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}	
		}	
		//TYPE SIMPLE
		else if (nbLexeme == 4)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
			m_size_a = 0;
			m_size_b = 0;
			itr = m_listLexemes.end();
			itr--;
		}
	
		//TYPE VECTOR
		else if (nbLexeme == 5)
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;
		}	

		else if (nbLexeme == 6)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str());
			m_size_a = prevNb;
			nbLexeme = 7;
		}	

		else if (nbLexeme == 7)
		{
			if (nextWord == "downto")
			{
				nbLexeme = 8;
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

		else if (nbLexeme == 8)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			m_size_b = nextNb;
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

		else if (nbLexeme == 10)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}
		
		// TYPE  RANGE
		else if (nbLexeme == 11)
		{
			if (nextWord != "range")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 12;
		}

		else if (nbLexeme == 12)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str());
			nbLexeme = 13;
		}

		else if (nbLexeme == 13)
		{
			if (nextWord != "to")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 14;
		}

		else if (nbLexeme == 14)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			if (nextNb <= prevNb)
			{
				m_msgBox.createMessage("211", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 15;
		}

		else if (nbLexeme == 15)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}

		count++;	
	}
}
