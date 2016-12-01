#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "PARSER/HEADER/Top.h"

using namespace std;

int main(int argc, char *argv[])
{
	Top myTop(argv[1]);
	//myTop.extractLexeme();
	
	vector<string> mytab;
	vector<string>::iterator itmytab;
	mytab.push_back("xtestx");
	mytab.push_back("xxx");
	mytab = myTop.cutCharacter(mytab, 120);
	for(itmytab=mytab.begin(); itmytab != mytab.end(); itmytab++)
	{
		cout << *itmytab << endl;
	}	
}
