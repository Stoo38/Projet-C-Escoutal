#include "../HEADER/Type.h"

void Type::verifySyntax() 
{/*
	
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
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
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
				nbLexeme = 11;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 10)
		{
			if (verifyNumber(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
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
			nbLexeme = 12;
		}

		else if (nbLexeme == 11)
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
			nbLexeme = 12;
		}

		else if (nbLexeme == 12)
		{
			if (nextWord != ")")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 13;
		}

		else if (nbLexeme == 13)
		{
			if (nextWord != "of")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 14;
		}	

		else if (nbLexeme == 14)
		{
			if (verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 15;
		}	

		else if (nbLexeme == 15)
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
		}


// Cas où l'on a une paranthèse ouvrante 

		else if (nbLexeme == 17)
		{
			if (verifyLabel(nextWord) == false)
			{	
				nbLexeme = 18;
			}
			else if (nextWord == "\'")
			{	
				nbLexeme = 20;
			}
			else if (nextWord == "\"" )
			{	
				nbLexeme = 24;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}
		
		// Cas d'un simple étiquette
		else if (nbLexeme == 18)
		{
			if (nextWord == ",")
			{
				nbLexeme = 19;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 28;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 19)
		{
			if (verifyLabel(nextWord) != false)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 18;
		}	

		// Cas d'un charactère encadré par deux apostrophes 'char'
		else if (nbLexeme == 20)
		{
			if ((verifyGlobalWord(nextWord) == false) && (nextWord.size() == 1))
			{
				nbLexeme = 21;
				cout << "BEEEELLLLLLLLLE" << endl;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
		}	

		else if (nbLexeme == 21)
		{
			if (nextWord != "\'")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;
		}

		else if (nbLexeme == 21)
		{
			if (nextWord != "\'")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 22;
		}

		else if (nbLexeme == 22)
		{
			if (nextWord == ",")
			{
				nbLexeme = 23;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 28;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 23)
		{
			if (nextWord != "\'")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 20;
		}	

		// Cas d'une suite de bits encadrée par deux guillemets "bits"

		else if (nbLexeme == 24)
		{
			string nextValue = "";
			for (int i=0; i < nextWord.size(); i++)
			{
				if ((nextWord[i] == 0) || (nextWord[i] == 1))
				{
					nextValue += nextWord[i];
				}
			}

			if (nextValue.size() < 2)
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 25;
		}

		else if (nbLexeme == 25)
		{
			if (nextWord != "\"")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 26;
		}

		else if (nbLexeme == 26)
		{
			if (nextWord == ",")
			{
				nbLexeme = 27;
			}
			else if (nextWord == ")")
			{	
				nbLexeme = 28;
			}
			else
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);
				itr = m_listLexemes.end();
				itr--;
			}
		}

		else if (nbLexeme == 27)
		{
			if (nextWord != "\"")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 24;
		}

		else if (nbLexeme == 28)
		{
			if (nextWord != ";")
			{
				m_msgBox.createMessage("212", (*itr).m_line, nextWord);		
				itr = m_listLexemes.end();
				itr--;
			}
			nbLexeme = 16;
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
	}*/
}
