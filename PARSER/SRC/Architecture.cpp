#include "../HEADER/Architecture.h"

const string & Architecture::getEntity() const		//Renvoie le nom de l'entity rattachee a l'architecture
{
	return m_entity.m_word;
}

void Architecture::createTree()			//Appelle les differentes fonctions pour repartir les lexemes	
{
	createComponent();
	createProcess();
	createType();
	createSignal();
	createPortMap();
	createConnexion();
	BlocNode::createTree();
}

void Architecture::createComponent()	//Repere les component entre le mot-clé "component" et la fin "end component;"
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inComponent = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "component")		//Debut du component
		{
			inComponent = true;
			itr++;
			m_listeBlocks.push_back(new Component((*itr).m_word, (*itr).m_line, m_msgBox));	//Creation d'un component
			Lexeme flag("FLAG_COMP", (*itr).m_line);		//Place un FLAG	 
			newList.push_back(flag);
			m_msgBox.createMessage("020", (*itr).m_line, (*itr).m_word);			
		}
		else if (((*itr).m_word == "end") && (inComponent == true))	
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "component")	//Fin du component
			{
				itr++;
				if ((*itr).m_word == ";")
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else
				{
					m_msgBox.createMessage("022", (*itr).m_line, "");
					newList.push_back(*itr);
				}
				inComponent = false;
			}
			else
			{
				m_msgBox.createMessage("022", (*itr).m_line, "");
			}
		}
		else 
		{
			if (inComponent == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout du lexeme au dernier component
			}
			else
			{
				newList.push_back(*itr);			//Ajout du lexeme a la nouvelle liste de lexeme
			}
		}	
	}
	m_listLexemes = newList;
}

void Architecture::createProcess()	//Repere les process entre le mot-clé process et "end process ;"
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inProcess = false;	
	bool labelProcess = false;		
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if (((*itr).m_word == "process") && (inProcess == false))	//Debut du process
		{
			inProcess = true;
			itr--;
			if ((*itr).m_word == ":")
			{
				labelProcess = true;
				itr--;
				m_listeBlocks.push_back(new Process((*itr).m_word, (*itr).m_line, m_msgBox));	//Creation du process avec etiquette
				m_msgBox.createMessage("021", (*itr).m_line, (*itr).m_word);	
				itr++;
				itr++;
				newList.pop_back();
				newList.pop_back();				
			}
			else
			{
				itr++;
				m_listeBlocks.push_back(new Process("default", (*itr).m_line, m_msgBox));	//Creation du process sans etiquette
				m_msgBox.createMessage("021", (*itr).m_line, "default");				
			}
			
			Lexeme flag("FLAG_PROC", (*itr).m_line);	//Place un FLAG		 
			newList.push_back(flag);
		}
		else if (((*itr).m_word == "end") && (inProcess == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			if ((*itr).m_word == "process")			//Fin du process
			{
				itr++;
				if ((labelProcess == false) && ((*itr).m_word == ";"))
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else if ((labelProcess == true) && ((*itr).m_word == ";"))
				{
					m_msgBox.createMessage("026", (*itr).m_line, "");
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
				}
				else if ((labelProcess == true) && ((*itr).m_word != ";"))
				{
					(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
					itr++;
					if ((*itr).m_word == ";")
					{
						(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
					}
					else
					{
						m_msgBox.createMessage("027", (*itr).m_line, "");
						newList.push_back(*itr);
					}
				}
				else
				{
					m_msgBox.createMessage("024", (*itr).m_line, "");
					newList.push_back(*itr);
				}
				inProcess = false;
				labelProcess = false;
			}
		}
		else 
		{
			if (inProcess == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout des lexemes au dernier process
			}
			else
			{
				newList.push_back(*itr);				//Ajout des lexemes a la nouvelle liste
			}
		}
	}	
	m_listLexemes = newList;
}

void Architecture::createType()	//Repere les type entre le mot-clé type et ";"
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inType = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "type")		//Detection du mot-cle type
		{
			inType = true;
			itr++;
			m_listeBlocks.push_back(new Type((*itr).m_word, (*itr).m_line, m_msgBox));	//Creation d'un type
			m_msgBox.createMessage("802", (*itr).m_line, (*itr).m_word);	
			Lexeme flag("FLAG_TYPE", (*itr).m_line);	//Place un FLAG			 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inType == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Fin du type
			inType = false;
		}
		else 
		{
			if (inType == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout du lexeme au dernier objet type cree
			}
			else
			{
				newList.push_back(*itr);	//Ajout du lexeme a la nouvelle liste
			}
		}	
	}
	m_listLexemes = newList;
}

void Architecture::createSignal()	//Repere les signaux entre le mot-clé signal et ";"
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inSignal = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if ((*itr).m_word == "signal")	//Debut du signal
		{
			inSignal = true;
			itr++;
			m_listeBlocks.push_back(new Signal((*itr).m_word, (*itr).m_line, m_msgBox));
			m_msgBox.createMessage("801", (*itr).m_line, (*itr).m_word);	
			Lexeme flag("FLAG_SIGN", (*itr).m_line);		//Place un FLAG		 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inSignal == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inSignal = false;
		}
		else 
		{
			if (inSignal == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout du lexeme au dernier objet signal cree
			}
			else
			{
				newList.push_back(*itr);		//Ajout du lexeme a la nouvelle liste
			}
		}	
	}
	m_listLexemes = newList;
}

void Architecture::createPortMap()	//Repere les portmap à partir du mot-cle port map
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inPortMap = false;			
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		if (((*itr).m_word == "port")&&(inPortMap == false))
		{
			itr++;
			if ((*itr).m_word == "map")
			{
				inPortMap = true;
				itr--;
				itr--;
				string name((*itr).m_word);
				itr--;
				itr--;
				m_listeBlocks.push_back(new PortMap((*itr).m_word, name, (*itr).m_line, m_msgBox));
				m_msgBox.createMessage("804", (*itr).m_line, (*itr).m_word);
				newList.pop_back();	
				newList.pop_back();	
				newList.pop_back();	
				Lexeme flag("FLAG_PMAP", (*itr).m_line);	//Place un FLAG			 
				newList.push_back(flag);
			}
			else
			{	
				itr--;
				newList.push_back(*itr);
			}
						
		}
		else if (((*itr).m_word == ";") && (inPortMap == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inPortMap = false;
		}
		else 
		{
			if (inPortMap == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout du lexeme au dernier objet portmap cree
			}
			else
			{
				newList.push_back(*itr);		//Ajout du lexeme a la nouvelle liste
			}
		}	
	}
	m_listLexemes = newList;
}

void Architecture::createConnexion()
{
	list <Lexeme>::iterator itr;
	list <Lexeme> newList;
	bool inConnex = false;
	
	int count = 0;
	string word;
	string nextWord;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		word = (*itr).m_word;
		nextWord = checkNextWord(count, itr);
		if ((word == "<") && (nextWord == "=") && (inConnex == false))
		{
			inConnex = true;
			m_listeBlocks.push_back(new Connexion((*itr).m_line, m_msgBox));
			m_msgBox.createMessage("815", (*itr).m_line, "");	
			itr--;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			newList.pop_back();
			itr++;
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	
			Lexeme flag("FLAG_CONNEX", (*itr).m_line);		//Place un FLAG		 
			newList.push_back(flag);			
		}
		else if (((*itr).m_word == ";") && (inConnex == true))
		{
			(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);
			inConnex = false;			
		}
		else 
		{
			if (inConnex == true)	
			{		
				(m_listeBlocks.back())->addLexeme((*itr).m_word, (*itr).m_line);	//Ajout du lexeme au dernier objet connexion cree
			}
			else
			{
				newList.push_back(*itr);		//Ajout du lexeme a la nouvelle liste
			}
		}
		count++;
	}
	m_listLexemes = newList;
}

void Architecture::verifySyntax() 
{
	
	list <Lexeme>::iterator itr;
	int nbLexeme = 0;
	int count = 0;
	
	string monword;
	string nextWord;
	for(itr = m_listLexemes.begin(); itr != m_listLexemes.end(); itr++)
	{
		monword = (*itr).m_word;
		nextWord = checkNextWord(count, itr);
		switch (nbLexeme)
		{
			case 0:			//Premier mot: architecture
				if (nextWord == m_identifiant.m_word)	//Second mot: nom de l'architecture
				{
					nbLexeme = 1;
				}
				else
				{
					m_msgBox.createMessage("230", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 1:
				if (nextWord == "of")		//Prochain mot: of
				{
					nbLexeme = 2;
				}
				else
				{
					m_msgBox.createMessage("231", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 2:
				if (verifyLabel(nextWord) == false)	//Prochain mot: nom de l'entite rattachee
				{
					nbLexeme = 3;
				}
				else
				{
					m_msgBox.createMessage("231", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 3:
				m_entity = (*itr);
				if (nextWord == "is")			//Prochain mot: is
				{
					nbLexeme = 4;
				}
				else
				{
					m_msgBox.createMessage("231", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 4:		//Prochain mot: un flag remplacant un component, un signal ou un type
				if ((nextWord == "FLAG_COMP") || (nextWord == "FLAG_SIGN") || (nextWord == "FLAG_TYPE"))
				{
					nbLexeme = 4;
				}
				else if (nextWord == "begin")	//Ou bien le begin d'architecture
				{
					nbLexeme = 5;
				}
				else
				{
					m_msgBox.createMessage("231", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 5:		//Prochain mot: un flag remplacant un port map, un process ou une connexion
				if ((nextWord == "FLAG_PMAP") || (nextWord == "FLAG_PROC") || (nextWord == "FLAG_CONNEX"))
				{					
					nbLexeme = 5;
				}
				else if (nextWord == "end")	//Ou bien le end d'architecture
				{
					nbLexeme = 6;
				}
				else
				{
					m_msgBox.createMessage("231", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 6:
				if (nextWord == m_identifiant.m_word)	//Prochain mot: le nom de l'architecture
				{
					nbLexeme = 7;
				}
				else
				{
					m_msgBox.createMessage("230", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 7:
				if (nextWord == ";")			//Prochain mot: doit etre un ";"
				{
					nbLexeme = 8;
				}
				else
				{
					m_msgBox.createMessage("232", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			case 8:
				if (nextWord != "")			//Il ne doit plus y avoir de lexeme dans l'architecture
				{
					m_msgBox.createMessage("232", (*itr).m_line, nextWord);
					itr = m_listLexemes.end();
					itr--;
				}
				break;
			default:
				break;
		}
		count++;
	}	
	BlocNode::verifySyntax();
}
