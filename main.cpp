#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//argc = number of strings in argv
//argv[] = table of pointers on strings
int main(int argc, char *argv[])
{
	cout << argv[1] << endl;	//Return the first parameter when we execute the program in the terminal
	cout << argv[2] << endl;	//Return the second parameter when we execute the program in the terminal
}
