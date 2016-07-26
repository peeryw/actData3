/*
Morse_Code.cpp file
*/

#include "Morse_Code.h"

Morse::Morse()
{
	treeMade = false;
	root = new tree;
	root->letter = "~";
	root->dotdash = "";
	root->Left = nullptr;		// no nodes
	root->Right = nullptr;
}

Morse::~Morse(){
	delete root;
}

string Morse::getLetter(const string& code)
//read in code, search through map to find key(code) and return letter
{
	map<string, string>::const_iterator it= dotToAscii.find(code);
	if (it != dotToAscii.end())
	{
		return it->second;
	}
	else
		return "";
}

string Morse::getCode(const string& letter)
//read in letter, search through map to find key(letter) and return code
{
	map<string, string>::const_iterator it = asciiToDot.find(letter);
	if (it != asciiToDot.end())
	{
		return it->second;
	}
	else
		return "";
}

//read in string
//step through string one "character" at a time, the delim will be a space
//send first character to getLetter
// returned character will be added to new string
//repeat step 3 and 4 untill string is empty
string Morse::decode(string code)
{	
	string decode; // result
	decode += getLetter(code.substr(0, code.find(" "))); // decode first substring and add to result
	
	while (code.find(" ") != -1){ // while there are still spaces in the string
		code = code.substr(code.find(" ") + 1); // slice decoded substring
		decode += getLetter(code.substr(0, code.find(" ")));
	}
	return string(decode);
}


string Morse::encode( string  letter)
{
	//read in string
	//step through one character at a time
	//characters will only be letters, string in will be single word only
	//send first character to getCode
	//returned code character will be added to new string
	//space needs to be added to new string after each character return
	//repeat until string is empty
	string TempString;
	string ENCODED;
	Morse TempCode;
	for (int i = 0; i < letter.length(); i++)
	{
		map<string, string>::const_iterator it = asciiToDot.find(letter[i]);
		if (it != asciiToDot.end())
		{
			 ENCODED += it->second;
		}
		else
			return "";
	}
	return string(ENCODED);
}

void Morse::makeLetter(string tempLetter, string letterDotdash){
	asciiToDot[tempLetter] = letterDotdash; // populate maps
	dotToAscii[letterDotdash] = tempLetter;
	tree **currTree = &root;				// Pointer to a pointer to root
	for (int i=0; i <= letterDotdash.length(); i++){
		if (letterDotdash[i]=='.'){			// dot = Navigate left
			if ((*currTree)->Left == nullptr){		// if node DNE
				(*currTree)->Left = new tree;		// make it as empty node
				currTree = &((*currTree)->Left);	// advance to dummy node
			}
			else {
				currTree = &((*currTree)->Left);	// node exists lets go
			}
		}
		if (letterDotdash[i]=='-' || letterDotdash[i]=='_'){ // dash = navigate right
			if ((*currTree)->Right == nullptr){
				(*currTree)->Right = new tree;
				currTree = &((*currTree)->Right); // go read the comments above
			}
		else {
				currTree = &((*currTree)->Right);
			}
		}
	}
	
	(*currTree)->dotdash=letterDotdash; // found the correct location
	(*currTree)->letter=tempLetter;		// set dots and letters
	
	if (asciiToDot.size() > 25){
		treeMade = true;				// Use this to keep other functions disabled
										// until tree is populated
	}
}
