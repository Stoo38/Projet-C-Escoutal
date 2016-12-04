#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "PARSER/HEADER/Top.h"

using namespace std;

int main(int argc, char *argv[])
{
	Top myTop(argv[1]);
	myTop.createTree();
}
