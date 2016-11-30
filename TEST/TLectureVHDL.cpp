#include <fstream>
#include <iostream>

using namespace std;

string toMinuscule(string word);
void extractLexeme();

int main()
{

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
