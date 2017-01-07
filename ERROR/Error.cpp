#include "Error.h"

void Error::createError(int nError, int nline, string lexeme)
{
    ifstream myFile(m_errorFileName.c_str());

	if(myFile)
	{
		string line;
		while(getline(myFile, line))
		{
			cout << line << endl;
            int i = stoi(line.substr(0,2), 0, 10);
			cout << i << endl;
		}
	}
	else
	{
        cout << "Can not access to the error file Error.txt" << endl;
	}
}

