#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "../DISPLAY/Display.h"

using namespace std;

int main()
{
	Display Box;
	Box.createMessage("06", 0, "architecture");	
	Box.createMessage("03", 4, "ok");	
	Box.createMessage("12", 120, "entity");
	Box.createMessage("04", 120, "component");
	Box.displayMessage(true);	
}
