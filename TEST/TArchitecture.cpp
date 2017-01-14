#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>

#include "../PARSER/HEADER/Top.h"		
#include "../DISPLAY/Display.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	Display messageBox(true);				
	messageBox.createMessage("01", 0, "VHDL/ALU.vhd");			
	Top myTop("VHDL/ALU.vhd", messageBox);				
	myTop.createTree();
	messageBox.displayMessage();				
}

