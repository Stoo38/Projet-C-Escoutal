#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector<string> split(vector<string> tab, int *numCase, const char symbol);
string cutCharacter(string sentence, const char symbol);
string cutComment(string sentence);

int main()
{
	//TEST 1	
	/*string test("testest");
	vector<string> tab;
	vector<string>::iterator it;
	tab.push_back(test);
	int a = 0;
	tab = split(tab, &a, 101);
	cout << "contenu tab main" << endl;
	it = tab.begin();
	for(it = tab.begin(); it != tab.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "a = " << a << endl;*/

	//TEST 2
	string test2("Ceci est                      un nouveau test grandeur nature ! ");
	cout << test2 << endl;
	test2 = cutCharacter(test2, 32);
	cout << test2 << endl;

	//TEST 3
	/*string test3("Ceci est un --autre test --");
	cout << test3 << endl;
	test3 = cutComment(test3);
	cout << test3 << endl;*/
	
}
	

vector<string> split(vector<string> tab, int *numCase, const char symbol)
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
	cout << "contenu tab" << endl;
	it = tab.begin();
	for(it = tab.begin(); it != tab.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "contenu tabstring" << endl;
	it = tabString.begin();
	for(it = tabString.begin(); it != tabString.end(); it++)
	{
		cout << *it << endl;
	}
	it = tab.begin();
	tab.insert(it+(*numCase), tabString.begin(), tabString.end());
	cout << "contenu tab" << endl;	
	it = tab.begin();
	tab.erase(it+ajout);
	for(it = tab.begin(); it != tab.end(); it++)
	{
		cout << *it << endl;
	}
	*numCase = ajout;
	return tab;
}

string cutCharacter(string sentence, const char symbol)
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
			sentence[sentence.size()-1] = 62;
			i = i - 1;
			nbErase = nbErase + 1;
		}
		cout << sentence << endl;
	}
	sentence = sentence.substr(0, sentence.size() - nbErase);
	return sentence;
}

string cutComment(string sentence)
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


