#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <cstdlib>

using namespace std;

class Display
{
   	protected:
	bool m_closeError;
   	string m_messageFileName;
	list <string> m_listMessages;
	int m_alreadyDisplayed;
   	public:
   	Display(bool closeError = true) :
	m_closeError(closeError),
	m_messageFileName("/home/phelma/Projet-C-Escoutal/DISPLAY/Messages.txt"),
	m_alreadyDisplayed(0)
   	{
		
   	}

    	void createMessage(string nMessage, int nline = 0, string lexeme = "");
	void displayMessage(bool allDisplay = false);
	vector<string> cutCharacter(vector<string> tab, const char symbol);	
};
#endif
