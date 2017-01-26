#include "../HEADER/Port.h"

void Port::reorganizeLexemes()
{
	m_listLexemes.pop_front();
}

/*

for (int i = 0; i < 7; i++)
{
	if ((monmot == myTypes[i]) && (i < 3))
	{
		//ici c'est les cas simples
		//...
		
		i = 7; //fin de boucle
	}
	else if ((monmot == myTypes[i]) && (i >= 3) && (i < 6))
	{
		//ici c'est les cas type vector
		//...
		
		i = 7; //fin de boucle
	}
	else if (monmot == myTypes[i])
	{
		//ici c'est les cas type range
		//...
		
		i = 7; //fin de boucle
	}
}
*/

void Port::verifySyntax() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;

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

		cout << count << " " << m_listLexemes.size() << " " << nbLexeme << " " << monword << " " << nextWord <<  endl;
	
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
			if(verifyLabel(nextWord) == false)
			{
				nbLexeme = 0;	
			}
			else
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 2)
		{	
			if ((nextWord == "in") || (nextWord == "in"))
			{	
				nbLexeme = 3;	
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
			for (int i = 0; i < 7; i++)
			{
				if ((nextWord == myTypes[i]) && (i < 3))
				{
					//ici c'est les cas simples
					nbLexeme = 4;
		
					i = 7; //fin de boucle
				}
				else if ((nextWord == myTypes[i]) && (i >= 3) && (i < 6))
				{
					//ici c'est les cas type vector
					nbLexeme = 5;
		
					i = 7; //fin de boucle
				}
				else if (nextWord == myTypes[i])
				{
					//ici c'est les cas type range
					nbLexeme = 11;
					i = 7; //fin de boucle
				}
				else
				{
					m_msgBox.createMessage("208", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}			
			}
		}	
		//TYPE SIMPLE
		else if (nbLexeme == 4)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("209", (*itr).m_line, nextWord);
			}
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
/*
		else if (nbLexeme == 6)
		{
			string h("ttest");
			int i;
			i = atoi(h.c_str());

			if (atoi(nextWord.c_str()) != "(")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 7;
		}	
*/
		else if (nbLexeme == 7)
		{
			if (nextWord != "upto" || nextWord != "downto" || nextWord != "to")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 8;
		}
/*
		else if (nbLexeme == 8)
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;
		}
*/
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
/*
		else if (nbLexeme == 12)
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 13;
		}
*/
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
/*
		else if (nbLexeme == 14)
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("207", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 15;
		}
*/
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



