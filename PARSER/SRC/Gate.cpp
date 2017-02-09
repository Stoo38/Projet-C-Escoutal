#include "../HEADER/Gate.h"

void Gate::reorganizeLexemes()
{
	m_listLexemes.pop_front();
	m_listLexemes.pop_front();
}

void Gate::verifySyntax()
{
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	string myGates[5];
	myGates[0] = "and";
	myGates[1] = "or";
	myGates[2] = "xor";
	myGates[3] = "nand";
	myGates[4] = "nor";
	
	string monword;
	string nextWord;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		monword = (*itr).m_word;
		nextWord = checkNextWord(count, itr);
		switch (nbLexeme)
		{
			case 0:		
				//if (monword == "not")			
			//Premier mot: nom du signal ou bien FLAG_GATE, correspond à une combinaison de signaux	
				if ((monword == "FLAG_GATE") || (verifyLabel(monword) == false))	
				{				
					if (nextWord == "")	 
					{
						itr = m_listLexemes.end();
						itr--;
					}
					else
					{
						bool flag = false;	
						for (int i = 0; i < 5; i++)	
						{				
							if (nextWord == myGates[i]) 
							{
								flag = true;
								nbLexeme = 1;
								i = 7; 
							}					
						}
						if (flag == false)
						{
							m_msgBox.createMessage("239", (*itr).m_line, monword);
							itr = m_listLexemes.end();
							itr--;
						}	
					}
				} 
				else
				{
					m_msgBox.createMessage("238", (*itr).m_line, monword);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 1:
				if ((nextWord == "FLAG_GATE") || (verifyLabel(nextWord) == false))	 
				{
					nbLexeme = 2;
				}
				else
				{
					m_msgBox.createMessage("238", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}				
				break;
			case 2:
				if (nextWord != "")	 
				{
					m_msgBox.createMessage("240", (*itr).m_line, nextWord);
				}
				itr = m_listLexemes.end();
				itr--;			
				break;
			default:
				break;
		}
		count++;
	}
}	

