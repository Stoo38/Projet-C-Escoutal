#include <fstream>
#include <iostream>
#include <list>
#include "../PARSER/HEADER/Top.h"

using namespace std;

int main()
{
	Top testtop("../VHDL/ALU.vhd");
	testtop.createBlocks();
}


