#include <fstream>
#include <iostream>
#include <list>
#include "../PARSER/HEADER/Top.h"
#include <vector>

using namespace std;

vector<string> split(const string &line, const char symbol);

int main()
{
	/*Top testtop("../VHDL/ALU.vhd");
	testtop.createBlocks();*/

	string test(";Ceci;est;un;test;");
	split(test, 59);
}



vector<string> split(const string &line, const char symbol)
{
	vector<string> tabString;
	int pos = 0;
	int posSymbol = 0;
	if (line.empty())
	{
		return tabString;
	}
	do
	{
		posSymbol = line.find(symbol, pos);
		if (posSymbol != string::npos)
		{
			if (posSymbol == 0)
			{
				cout << line.substr(pos, 1) << endl;
				tabString.push_back(line.substr(pos, 1));
				pos++;
			}
			else if (posSymbol == line.size() - 1)
			{				
				cout << line.substr(pos, posSymbol - pos) << endl;
				tabString.push_back(line.substr(pos, posSymbol - pos));
				pos = posSymbol;
				cout << line.substr(pos, 1) << endl;
				tabString.push_back(line.substr(pos, 1));
			}
			else
			{
				cout << line.substr(pos, posSymbol - pos) << endl;
				tabString.push_back(line.substr(pos, posSymbol - pos));
				pos = posSymbol;
				cout << line.substr(pos, 1) << endl;
				tabString.push_back(line.substr(pos, 1));
				pos = posSymbol+1;
			}
		}
		else
		{
			tabString.push_back(line.substr(pos, line.size()));
			cout << line.substr(pos, line.size()) << endl;
			pos = posSymbol;
		}
	} while (pos != line.size() - 1);
	return tabString;
}


