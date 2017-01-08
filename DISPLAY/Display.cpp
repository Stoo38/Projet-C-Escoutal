#include "Display.h"

//Fonction pour creer un message à partir d'un numéro de message, d'un numéro de ligne et d'un mot
void Display::createMessage(string nMessage, int nline, string lexeme)
{
	ifstream myFile(m_messageFileName.c_str());	

	if(myFile)
	{
		string line;
		stringstream ssline;
		while(getline(myFile, line))
		{			
			if (line.substr(0,2) == nMessage)	//Recherche du texte correspondant au numero de message voulu
			{
				vector<string> message;
				vector<string>::iterator itmessage;
				message.push_back(line);
				message = cutCharacter(message, 32);
				for(itmessage=message.begin(); itmessage != message.end(); itmessage++)	//Remplacement des balises par un mot et/ ou une ligne
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
		if (line.substr(2,3) == "FAT")			//Si l'erreur ajoutée est de type Fatal Error, on arrête l'exécution
		{
			createMessage("03");
			displayMessage();
			exit(1);
		}	
		else if ((line.substr(2,3) == "ERR") && (m_closeError == true))	//On arrête également si une erreur a été rencontrée et que l'option correspondante est active
		{
			createMessage("04");
			displayMessage();
			exit(1);
		}
	}
	else
	{
        cout << "00WAR Warning: Can not access to the message file Messages.txt" << endl;
	}
}

//Fonction pour afficher les messages stockés
void Display::displayMessage(bool allDisplay)
{
	int counterDisplay =0;
 	int toDisplay;
	if (allDisplay == true)	//On test si on doit afficher tous les messages depuis le début ou seulement ceux pas encore affichés
	{
		toDisplay = 0;
	}
	else
	{
		toDisplay = m_alreadyDisplayed;
	}

	list <string>::iterator itlistMessages;	
	for(itlistMessages = m_listMessages.begin(); itlistMessages != m_listMessages.end(); itlistMessages++)	//Parcourt la liste des messages stockés
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
