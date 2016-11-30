#include <fstream>
#include <iostream>
#include <list>

using namespace std;

string toMinuscule(string word);
void extractLexeme();

int main()
{
	/*list <string> testlist;
	int i = 0;
	string c = "ccc";
	testlist.push_back(c);
	if (i = 0)
	{
		string a = "aaa";
		string b = "bbb";
		testlist.push_back(a);
		testlist.push_back(b);
	}
	cout << testlist.back() << endl;
	cout << testlist.front() << endl;*/

	list <string> testlist;
	int i = 0;
	string c = "ccc";
	string a = "aaa";
	
	testlist.push_back(c);
	testlist.push_back(a);
	if (1)
	{	
		string b = "bbb";
		testlist.push_back(b);
		cout << testlist.size() << endl;
	}
	cout << testlist.back() << endl;
	cout << testlist.front() << endl;	
	cout << testlist.size() << endl;
}

void extractLexeme ()
{
	ifstream monFlux("../VHDL/ALU.vhd");

	if(monFlux)
	{
		string word;
		while (monFlux.eof() != 1)
		{
			monFlux >> word;
			cout << word << endl;	
		}		
		
	}
	else
	{
		cout << "ERROR: File not found" << endl;
	}
}

string toMinuscule(string word)
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
