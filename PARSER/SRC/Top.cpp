#include "../HEADER/Top.h"

void Top::createTree()
{
	ifstream myFile(m_vhdlFileName.c_str());  	//Créé flux à partir du fichier VHDL

	if(myFile)					//Ouvre le fichier VHDL
	{
		m_msgBox.createMessage("05", 0, m_vhdlFileName);		//Crée un message indiquant que le fichier a bien été ouvert
		string line;
		vector<string> tab;
		vector<string>::iterator it;
		int counterLine = 1;						//Variable pour compter le numéro des lignes
		while(getline(myFile, line))					//Lit le fichier ligne par ligne
		{
			if (line != "")
			{
				line = eraseComment(line);			//Efface les commentaires
				line = toMinuscule(line);			//Transforme les minuscules en majuscules
				tab.push_back(line);				
				tab = cutSpecialCharacter(tab);			//Découpe la ligne en fonction des caractères spéciaux
				tab = eraseSpace(tab);				//Supprime les espaces, tabulations et éléments vides
				instanceClass(tab, counterLine);
				tab.clear();					//Vide la liste pour une prochaine ligne
			}
			counterLine++;
		}					
	}
	else
	{
		m_msgBox.createMessage("02", 0, m_vhdlFileName);		//Crée une erreur si le fichier VHDL ne s'ouvre pas
	}	
}

//Parcourt le mot caractere par caractere
//Si l'un d'eux est une majuscule, il est remplace par la minuscule correspondante
string Top::toMinuscule(string word)
{	
	for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (word[i] == j+65)
			{
				word[i] = j+97;
			}	
		}
	}
	
	return word;
}

//Parcourt le fichier a la recherche de --, utilises pour les commentaires en VHDL
//Supprime la fin du string a partir de ces symboles
string Top::eraseComment(string sentence)
{
	int taille = sentence.size();
	for(int i = 0; i < (taille - 1); i++)
	{
		if((sentence[i] == '-') && (sentence[i+1] == '-'))
		{
			if(i == 0)
			{
				sentence.clear();	
			}
			else
			{
				sentence = sentence.substr(0, i);
			}
			i = sentence.size() - 1;
		}
	} 
	return sentence;
}

//Fonction supprimant toutes les iterations d'un caractere defini
//Utilise le principe du decalage a gauche pour supprimer le caractere voulu
//La chaine de caractere est raccourcie a la fin si necessaire
string Top::eraseCharacter(string sentence, const char symbol)
{
	int nbErase = 0;
	for (int i = 0; i < sentence.size(); i++)
	{
		if(sentence[i] == symbol)
		{	
			for (int j = i; j < (sentence.size()-1); j++)
			{
				sentence[j] = sentence[j+1];			
			}
			sentence[sentence.size()-1] = 'x';
			i = i - 1;
			nbErase = nbErase + 1;
		}
	}
	sentence = sentence.substr(0, sentence.size() - nbErase);
	return sentence;
}

//Redecoupe une chaine de caractere en entree en fonction d'un caractere
//EXEMPLE: Pour e: "Testest" ---> "T" "e" "st "e" "st"
vector<string> Top::cutCharacter(vector<string> tab, const char symbol)
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

vector<string> Top::eraseSpace(vector<string> tab)
{		
	tab = cutCharacter(tab, 32);
	tab = cutCharacter(tab, 9);
	vector<string> tab2;
	vector<string>::iterator it;
	for(it = tab.begin(); it < tab.end(); it++)
	{
		
		if (*it != "" && *it != " " && *it != "	")
		{
			tab2.push_back(*it);
				
		}
	}
	return tab2;
}

vector<string> Top::cutSpecialCharacter(vector<string> tab)
{
	char i;

	for (i = 33; i < 127; i++)
	{
		tab = cutCharacter(tab,i);
		
		if (i == 47)
		{
			i = 57;
		}
		if (i == 64)
		{
			i = 90;
		}
		if (i == 94)
		{
			i = 95;
		}
		if (i == 96)
		{
			i = 122;
		}
	}
	return tab;	
}

void Top::instanceClass(vector<string> tab, int nLine)
{
	vector<string>::iterator it;
	for(it=tab.begin(); it != tab.end(); it++)
	{
		if (*it == "library")
		{
			it++;
			m_listeBlocks.push_back(new Library(*it, nLine, m_msgBox));
			m_msgBox.createMessage("09", nLine, *it);
		}
		else if (*it == "entity")
		{
			it++;
			m_listeBlocks.push_back(new Entity(*it, nLine, m_msgBox));
			m_msgBox.createMessage("10", nLine, *it);
		}
		else if (*it == "architecture")
		{
			it++;
			m_listeBlocks.push_back(new Architecture(*it, nLine, m_msgBox));
			m_msgBox.createMessage("11", nLine, *it);
		}
		else 
		{
			if (m_listeBlocks.size() > 0)
			{	
				(m_listeBlocks.back())->addLexeme(*it, nLine);
			}
			else
			{
				m_msgBox.createMessage("12", nLine, *it);
			}
		}
	}	
}

void Top::displayLexemes()
{
	list <Bloc *>::iterator it;
	for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
	{
		(*it)->displayLexemes();
	}
}
