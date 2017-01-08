#include "Display.h"

void Display::createMessage(string nMessage, int nline, string lexeme)
{
	ifstream myFile(m_messageFileName.c_str());	

	if(myFile)
	{
		string line;
		stringstream ssline;
		while(getline(myFile, line))
		{			
			if (line.substr(0,2) == nMessage)
			{
				vector<string> message;
				vector<string>::iterator itmessage;
				message.push_back(line);
				message = cutCharacter(message, 32);
				for(itmessage=message.begin(); itmessage != message.end(); itmessage++)
				{
					
					if (*itmessage == "<L:>")
					{
						ssline << nline << ":";
					}
					else if (*itmessage == "<\"W\">")
					{
						ssline << "\"" << lexeme << "\"";
					}
					else
					{
						ssline << *itmessage;
					}
				}					
				myFile.seekg(0, ios::end);				
			}								
		}
		line.clear();
		line = ssline.str();
		m_listMessages.push_back(line);
		if (line.substr(2,3) == "FAT")
		{
			createMessage("03");
			displayMessage();
			exit(1);
		}	
		else if ((line.substr(2,3) == "ERR") && (m_closeError == true))
		{
			createMessage("04");
			displayMessage();
			exit(1);
		}
	}
	else
	{
        cout << "Can not access to the message file Messages.txt" << endl;
	}
}

void Display::displayMessage(bool allDisplay)
{
	int counterDisplay =0;
 	int toDisplay;
	if (allDisplay == true)
	{
		toDisplay = 0;
	}
	else
	{
		toDisplay = m_alreadyDisplayed;
	}

	list <string>::iterator itlistMessages;	
	for(itlistMessages = m_listMessages.begin(); itlistMessages != m_listMessages.end(); itlistMessages++)
	{
		if (counterDisplay == toDisplay)
		{
			cout << *itlistMessages << endl;
			toDisplay++;
		}
		counterDisplay++;
	}
	m_alreadyDisplayed = toDisplay;
}

vector<string> Display::cutCharacter(vector<string> tab, const char symbol)
{
	vector<string> finalTab;
	vector<string>::iterator it;
	int pos;
	int posSymbol;
	string word = "";	
	for(it = tab.begin(); it < tab.end(); it++)
	{
		pos = 0;
		posSymbol = 0;
		word = *it;
		posSymbol = word.find(symbol, pos);
		do
		{
			if (posSymbol != string::npos)
			{
				if ((posSymbol - pos) == 0)
				{
					finalTab.push_back(word.substr(pos, 1));
					pos++;
					posSymbol = word.find(symbol, pos);
				}	
				else
				{
					finalTab.push_back(word.substr(pos, posSymbol - pos));
					pos = posSymbol;
					finalTab.push_back(word.substr(pos, 1));
					pos = posSymbol+1;
					posSymbol = word.find(symbol, pos);
				}
			}
			if(posSymbol == string::npos)
			{
				if(word.substr(pos, word.size()) != "")
				{
					finalTab.push_back(word.substr(pos, word.size()));
				}	
			}
		} while (posSymbol != string::npos);
	}
	
	
	return finalTab;
}
