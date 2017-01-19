#ifndef _STRING_FUNCTIONS_H_
#define _STRING_FUNCTIONS_H_

#include <vector>
#include <string>

using namespace std;

//FONCTIONS RETOURNANT UN STRING
//Fonction remplacant toutes les majuscules se trouvant dans le string en entree par des minuscules
string toMinuscule(string word);
//Fonction enlevant toutes les iterations d'un meme caractere dans un string
string eraseCharacter(string sentence, const char symbol);
//Fonction detectant un commentaire VHDL dans un string et effacant tous les caracteres correspondants
string eraseComment(string sentence);



//FONCTIONS RETOURNANT UN VECTOR<STRING>
//Fonction decoupant en plusieurs string un vector<string> en entree, en fonction d'un caractere defini
//EXEMPLE: Pour e: "Testest" ---> "T" "e" "st "e" "st"
vector<string> cutCharacter(vector<string> tab, const char symbol);	
//Fonction decoupant en fonction des espaces, puis supprimant toutes les chaines de caractères vides
vector<string> eraseSpace(vector<string> tab);
//Fonction decoupant en plusieurs string un vector<string> en entree, en fonction de tous les caractères spéciaux
vector<string> cutSpecialCharacter(vector<string> tab);

#endif	
