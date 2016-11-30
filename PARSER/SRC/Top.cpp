#include "../HEADER/Top.h"

void Top::createBlocks()
{
	ifstream myFile(m_vhdlFileName.c_str());

	if(myFile)
	{
		do		
		{
		} while (myFile.eof() != 1);		
	}
	else
	{
		cout << "ERROR: " << m_vhdlFileName << " not found" << endl;
	}
}

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

string Top::cutComment(string sentence)
{
	for(int i = 0; i < (sentence.size() - 1); i++)
	{
		if((sentence[i] == '-') && (sentence[i+1] == '-'))
		{
			sentence = sentence.substr(0, i);
			i = sentence.size();
		}
	} 
	return sentence;
}

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

vector<string> Top::cutCharacter(vector<string> tab, int *numCase, const char symbol)
{
	vector<string> tabString;
	vector<string>::iterator it;
	it = tab.begin();
	string word = *(it+(*numCase));
	int pos = 0;
	int posSymbol = 0;
	int ajout = 0;

	if (word.empty())
	{
		*numCase = 0;
		return tab;
	}

	do
	{
		posSymbol = word.find(symbol, pos);
		if (posSymbol != string::npos)
		{
			if (posSymbol == 0)
			{
				tabString.push_back(word.substr(pos, 1));
				ajout++;
				pos++;
			}
			else if (posSymbol == word.size() - 1)
			{
				tabString.push_back(word.substr(pos, posSymbol - pos));
				ajout++;
				pos = posSymbol;
				tabString.push_back(word.substr(pos, 1));
				ajout++;
			}
			else
			{
				tabString.push_back(word.substr(pos, posSymbol - pos));
				ajout++;
				pos = posSymbol;
				tabString.push_back(word.substr(pos, 1));
				pos = posSymbol+1;
				ajout++;
			}
		}
		else
		{
			tabString.push_back(word.substr(pos, word.size()));
			ajout++;
			pos = posSymbol;
		}
	} while (posSymbol != string::npos);
	it = tab.begin();
	tab.insert(it+(*numCase), tabString.begin(), tabString.end());
	it = tab.begin();
	tab.erase(it+ajout);
	*numCase = ajout;
	return tab;
}
