#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "../PARSER/HEADER/Top.h"

using namespace std;

int main()
{
	Top my_top("../VHDL/ALU.vhd");

	vector<string> mytab;
	vector<string>::iterator itmytab;
	mytab.push_back("te st");
	mytab.push_back("essai");
	mytab.push_back("test ");
	mytab.push_back("1 2 3 4 5");
	mytab = my_top.eraseSpace(mytab, 32);
	for(itmytab=mytab.begin(); itmytab != mytab.end(); itmytab++)
	{
		cout << *itmytab << endl;
	}
}
