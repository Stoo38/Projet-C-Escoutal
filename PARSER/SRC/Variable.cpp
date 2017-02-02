#include "../HEADER/Variable.h"

void Variable::verifySyntax() 
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	int nextNb = 0, prevNb = 0;
	int sizeVector = 0;

	string myTypes[3];
	myTypes[0] = "bit";
	myTypes[1] = "bit_vector";
	myTypes[2] = "unsigned";

	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		string monword = (*itr).m_word;
		string nextWord = checkNextWord(count, itr);

	
		if (nbLexeme == 0)
		{	
			if(verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;						
		}

		else if (nbLexeme == 1)
		{
			if (nextWord == ",")
			{
				nbLexeme = 2;
			}
			else if (nextWord == ":")
			{
				nbLexeme = 3;
			}
			else
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 2)
		{	
			if(verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 1;		
		}	

		else if (nbLexeme == 3)
		{
			bool flag = false;
			for (int i = 0; i < 3; i++)
			{
				if ((nextWord == myTypes[i]) && (i < 1))
				{
					//ici c'est les cas simples
					flag = true;
					nbLexeme = 4;
					i = 3; //fin de boucle
					
				}
				else if (nextWord == myTypes[i])
				{
					//ici c'est les cas type vector/unsigned
					flag = true;
					nbLexeme = 10;		
					i = 3; //fin de boucle
				}
			}
			if (flag == false)
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}	
		}	
		//TYPE SIMPLE
		else if (nbLexeme == 4)
		{
			if (nextWord == ";")
			{
				nbLexeme = 22;
			}
			else if (nextWord == ":")
			{
				nbLexeme = 5;
			}
			else
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 5)
		{	
			if(nextWord != "=")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 6;		
		}	

		else if (nbLexeme == 6)
		{	
			if(nextWord != "\'")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 7;		
		}	

		else if (nbLexeme == 7)
		{	
			if((nextWord.size() == 1) &&  ((nextWord[0] == '0') || (nextWord[0] == '1')))
			{
				nbLexeme = 8;
			}
			else
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}					
		}

		else if (nbLexeme == 8)
		{	
			if(nextWord != "\'")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 9;		
		}

		else if (nbLexeme == 9)
		{	
			if(nextWord != ";")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;		
		}


	
		//TYPE VECTOR ET UNSIGNED
		else if (nbLexeme == 10)
		{
			if (nextWord != "(")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 11;
		}

		else if (nbLexeme == 11)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			prevNb = atoi(nextWord.c_str());
			nbLexeme = 12;
		}	

		else if (nbLexeme == 12)
		{
			if (nextWord == "downto")
			{
				nbLexeme = 13;
			}
			else if (nextWord == "to")
			{
				nbLexeme = 14;
			}
			else
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 13)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nextNb = atoi(nextWord.c_str());
			if (nextNb >= prevNb)
			{
				m_msgBox.createMessage("210", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			sizeVector = (prevNb - nextNb);
			nbLexeme = 15;
		}

		else if (nbLexeme == 14)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
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
			sizeVector = (nextNb - prevNb);
			nbLexeme = 15;
		}

		else if (nbLexeme == 15)
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}	

		else if (nbLexeme == 16)
		{
			if (nextWord == ";")
			{
				nbLexeme = 22;
			}
			else if (nextWord == ":")
			{
				nbLexeme = 17;
			}
			else
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 17)
		{	
			if(nextWord != "=")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 18;		
		}	

		else if (nbLexeme == 18)
		{	
			if(nextWord != "\"")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 19;		
		}	

		else if (nbLexeme == 19)
		{	
			if ( nextWord.size() == (sizeVector+1))
			{
				for (int i=0; i < nextWord.size(); i++)
				{
					if ((nextWord[i] != '0') && (nextWord[i] != '1'))
					{	
						m_msgBox.createMessage("219", (*itr).m_line, nextWord);		
						itr = m_listLexemes.end();
						itr--;
						i = nextWord.size();
					}
				}
			}

			else
			{
				m_msgBox.createMessage("218", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 20;					
		}

		else if (nbLexeme == 20)
		{	
			if(nextWord != "\"")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 21;		
		}

		else if (nbLexeme == 21)
		{	
			if(nextWord != ";")
			{
				m_msgBox.createMessage("219", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;		
		}


		else if (nbLexeme == 22)
		{
			if (nextWord != "")
			{	
				m_msgBox.createMessage("220", (*itr).m_line, nextWord);
			}
			itr = m_listLexemes.end();
			itr--;
		}
		count++;	
	}
}
