#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int opt_nb_file = 1;
	bool opt_close_error = true;
	bool step_tree = false;	
	list <string> file;
	
	int i = 1;
	string parameter;
	for(int i = 1; i < argc; i++)
	{
		parameter = argv[i];
		if (parameter == "-file")
		{
			for (int j = i; j < argc; j++)
			{
				string parameter2 = argv[j];
				if (parameter2 == "-nb_files")
				{	
					opt_nb_file = atoi(argv[j+1]);									
					j = argc;					
				}
			}
			for (int j = 0; j < opt_nb_file; j++)
			{
				i++;
				file.push_back(argv[i]);					
			}					
		}
		else if (parameter == "-nb_files")
		{
			i++;	
			opt_nb_file = atoi(argv[i]);
		}
		else if (parameter == "-tree")
		{
			step_tree = true;	
		}
		else
		{
			cout << "invalid parameter" << endl;
		}
	}

	list <string>::iterator it;
	for (it = file.begin(); it != file.end(); it++)
	{
		cout << *it << endl;
	}
		
}

/*int main(int argc, char *argv[])
{
	string function(argv[1]);
	string file(argv[2]);
	if (function == "tree")
	{
		Top myTop(file);
		myTop.createTree();		
	}
	else
	{
		cout << "Premier parametre incorrect: le choix de la fonction n'est pas valide" << endl;
	}


	
}*/
