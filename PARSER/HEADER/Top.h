#ifndef _TOP_H_
#define _TOP_H_

#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "Bloc.h"

using namespace std;

class Top
{
	private:
	string m_vhdlFileName;
	//list < *Bloc > m_listeBlocks;

	public:
	Top(const string vhdlFileName = ""):
	m_vhdlFileName(vhdlFileName)
	{
		//m_listeBlocks.clear();	
	}

	void createBlocks();
	string toMinuscule(string word);
};

#endif	
