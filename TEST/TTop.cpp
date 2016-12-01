#include <fstream>
#include <iostream>
#include <list>
#include <vector>
/*#include "../PARSER/HEADER/Top.h"*/

using namespace std;

int main()
{
	/*Top my_top("../VHDL/ALU.vhd");

	vector<string> mytab;
	vector<string>::iterator itmytab;
	mytab.push_back("texst");
	mytab.push_back("essai");
	mytab.push_back("testx");
	mytab.push_back("1x2x3x4x5");
	mytab = my_top.eraseSpace(mytab);
	for(itmytab=mytab.begin(); itmytab != mytab.end(); itmytab++)
	{
		cout << *itmytab << endl;
	}*/

	ifstream myFile("../VHDL/test.vhd");

	if(myFile)
	{
		string line;
		while(getline(myFile, line))		
		{
			cout << line << endl;
			cout << 1 << endl;
		} 
				
	}
	else
	{
		cout << "ERROR:  not found" << endl;
	}
}
