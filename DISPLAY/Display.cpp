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
			if (line.substr(0,3) == nMessage)	//Recherche du texte correspondant au numero de message voulu
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
		if (line.substr(3,3) == "FAT")			//Si l'erreur ajoutée est de type Fatal Error, on arrête l'exécution
		{
			createMessage("003");
			displayMessage();
			exit(1);
		}	
		else if ((line.substr(3,3) == "ERR") && (m_closeError == true))	//On arrête également si une erreur a été rencontrée et que l'option correspondante est active
		{
			createMessage("004");
			displayMessage();
			exit(1);
		}
	}
	else
	{
        cout << "000WAR Warning: Can not access to the message file Messages.txt" << endl;
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
			if ((*itlistMessages).substr(3,3) != "DEB")
			{
				cout << *itlistMessages << endl;
			}
			else if (((*itlistMessages).substr(3,3) == "DEB")&&(m_debugger == true))
			{
				cout << *itlistMessages << endl;
			}			
			toDisplay++;
		}
		/*if (counterDisplay == toDisplay)
		{
			cout << *itlistMessages << endl;
			cout << (*itlistMessages).substr(3,3) << endl;
			toDisplay++;
		}
		if ((counterDisplay == toDisplay) && (m_debugger == true))
		{
			cout << *itlistMessages << endl;
			toDisplay++;
		}
		else if ((counterDisplay == toDisplay) && ((*itlistMessages).substr(3,3) != "DEB"))
		{
			cout << *itlistMessages << endl;
			toDisplay++;
		}*/
		counterDisplay++;
	}
	m_alreadyDisplayed = toDisplay;
}
