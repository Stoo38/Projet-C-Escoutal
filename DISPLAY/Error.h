#ifndef _ERROR_H_
#define _ERROR_H_

#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;

class Error
{
    protected:
    string m_errorFileName = "Error.txt";
    public:
    Error()
    {

    }

    void createError(int nError, int nline, string lexeme);
};
#endif
