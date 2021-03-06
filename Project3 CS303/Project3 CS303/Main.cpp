/*
Name:	Jack Goza, Joshua Ford, Scott Peery
Course:	CS303
Program:	Project 3
Due Date: 26 July 2016

Description: this program is for morse code. a tree will be used to create the morse code
structure for coding and decoding. the total depth of the tree should be 4. the root node
is of depth 0 and stores no letter. the program will be able to read in a file to create
the tree. to find the position of the letter, scan the code and branch left for dot or branch
right for dash. encoding will be done by replacing its letter with its code symbole. a space will
be used as a delimiter symbol between coded letters.(map maybe used to store code for letters
as well)

test input file is located at:
https://www.dropbox.com/s/3cj8yb8gcdsrefg/morse.txt?dl=0

Inputs: read in file to create tree. this will be a txt file. there is no need to use menu-based 
system for user or get input from the user. input can be called directly from main function.

Outputs: out put to new txt or to screen. the project does not specify which, so assumtion will
be both. output will be called from the main function. no need for menu-based system or user
selection for output.

Algorithm:
Create class for morse code tree
Read in txt file
create binary tree
Main function will call in txt file
Error check for file exists
Main function calls for decoding message
Error checking
Main function calls for encoding message
Error checking

*****SPECIAL NOTE*****
extra credit for using GitHub

*/

#include<iostream>
#include<fstream>
#include "Morse_Code.h"

using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;
	string code, value, temp;
	char letter;
	Morse_Code MorseCode;

	// 1. check file exists
	try
	{
		fin.open("morse.txt");
	}
	catch (exception e)
	{
		cerr << "Unable to open file." << endl;
		cout << "Unable to open txt file" << "\n" << "Program will now exit." << endl;
		system("pause");
		exit(0);
	}

	//2. Read in data from files
	while (!fin.eof())//while there is data to read
	{
		fin >> value;

		string::iterator it;
		int index = 0;
		for (it = value.begin(); it < value.end(); ++it, ++index) {
			if (isalnum(*it)) {//determine if is a letter value
				letter = *it;
			}
			if (index != 0 && index <= 4) {
				if (!isalnum(*it)) {//get the rest of the info from the line
					code += *it;
				}
			}
		}
		MorseCode.makeTree(letter, code);//buiilds tree and populates maps
		code = "";//clear code after each iteration
	}
	
	//currently test strings
	//change the string to test for different outcomes
	cout << MorseCode.decode(".... .. ._.. ._.. ._ ._. _.__ ._. .. __. __. . _.. _ .... . .__. ._. .. __ ._ ._. _.__ ") << endl;
	cout << MorseCode.encode("helpimtrappedinacomputer") << endl;

	system("pause");
	return 0;
}