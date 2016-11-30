#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector<string> split(vector<string> tab, const char symbol);

int main()
{
	vector<string> mytab;
	vector<string>::iterator itmytab;
	mytab.push_back("test");
	mytab.push_back("essai");
	mytab.push_back("test");
	mytab.push_back("12345");
	mytab = split(mytab, 101);
	for(itmytab=mytab.begin(); itmytab != mytab.end(); itmytab++)
	{
		cout << *itmytab << endl;
	}
}
vector<string> split(vector<string> tab, const char symbol)
{
	vector<string> tabString;
	vector<string> finalTab;
	vector<string>::iterator it;
	int pos;
	int posSymbol;
	int ajout;
	string word;	
	for(it = tab.begin(); it < tab.end(); it++)
	{
		pos = 0;
		posSymbol = 0;
		ajout = 0;
		word = *it;
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
		finalTab.insert(finalTab.end(), tabString.begin(), tabString.end());
		tabString.clear();
	}
	return finalTab;
}
