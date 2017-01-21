#include "../HEADER/Top.h"

void Top::createTree()
{
	ifstream myFile(m_vhdlFileName.c_str());  	//Créé flux à partir du fichier VHDL

	if(myFile)					//Ouvre le fichier VHDL
	{
		m_msgBox.createMessage("005", 0, m_vhdlFileName);		//Crée un message indiquant que le fichier a bien été ouvert
		string line;
		vector<string> tab;
		vector<string>::iterator it;
		int counterLine = 1;						//Variable pour compter le numéro des lignes
		while(getline(myFile, line))					//Lit le fichier ligne par ligne
		{
			if (line != "")
			{
				line = eraseComment(line);			//Efface les commentaires
				line = toMinuscule(line);			//Transforme les minuscules en majuscules
				tab.push_back(line);				
				tab = cutSpecialCharacter(tab);			//Découpe la ligne en fonction des caractères spéciaux
				tab = eraseSpace(tab);				//Supprime les espaces, tabulations et éléments vides
				instanceClass(tab, counterLine);
				tab.clear();					//Vide la liste pour une prochaine ligne
			}
			counterLine++;
		}

		list <Bloc *>::iterator it2;
		for(it2=m_listeBlocks.begin(); it2 != m_listeBlocks.end(); it2++)
		{
			(*it2)->createTree();
		}					
	}
	else
	{
		m_msgBox.createMessage("002", 0, m_vhdlFileName);		//Crée une erreur si le fichier VHDL ne s'ouvre pas
	}	
}

void Top::instanceClass(vector<string> tab, int nLine)
{
	vector<string>::iterator it;
	for(it=tab.begin(); it != tab.end(); it++)
	{
		if (*it == "library")
		{
			it++;
			m_listeBlocks.push_back(new Library(*it, nLine, m_msgBox));
			m_msgBox.createMessage("009", nLine, *it);
		}
		else if (*it == "entity")
		{
			it++;
			m_listeBlocks.push_back(new Entity(*it, nLine, m_msgBox));
			m_msgBox.createMessage("010", nLine, *it);
		}
		else if (*it == "architecture")
		{
			it++;
			m_listeBlocks.push_back(new Architecture(*it, nLine, m_msgBox));
			m_msgBox.createMessage("011", nLine, *it);
		}
		else 
		{
			if (m_listeBlocks.size() > 0)
			{	
				(m_listeBlocks.back())->addLexeme(*it, nLine);
			}
			else
			{
				m_msgBox.createMessage("012", nLine, *it);
			}
		}
	}	
}

void Top::displayLexemes()
{
	list <Bloc *>::iterator it;
	for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
	{
		(*it)->displayLexemes();
	}
}

void Top::verifySyntax()
{
	list <Bloc *>::iterator it;
	for(it=m_listeBlocks.begin(); it != m_listeBlocks.end(); it++)
	{
		(*it)->verifySyntax();
	}
	m_msgBox.createMessage("070", 0, "");
}
