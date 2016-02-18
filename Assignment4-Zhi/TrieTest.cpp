#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

int main(int argc, char** argv) {
	
	/* print a message and exit the program if the argument count is not 3*/
	if(argc != 3) {
		cout << "The number of arguments is wrong." << endl;
		return 0;
	}

	Trie trie;

	/* read the file from the first arguement and name the stream as "input"*/
	ifstream input(argv[1]);
	/* add the words in the file to trie*/
	for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();

	/* read the file from the first arguement and name the stream as "queries"*/
	ifstream queries(argv[2]);
	/* search each query in the second file*/
	for(string queryStr; getline(queries, queryStr);)
		if(trie.isWord(queryStr))
			cout << queryStr << " is found" << endl;
		else {
			vector<string> v = trie.allWordsWithPrefix(queryStr);
			if(v.size() !=0 )
			{
				/* if the word is not found, return vector of strings which has the word as prefix*/
				cout << queryStr << " is not found, did you mean:" << endl;
				/* print the strings in the vector*/
				//cout << "   " << v[i] << endl;
				for (int i = 0; i < v.size();i++) 
					cout << "   " << v[i] << endl;
			}
			else
				{
				cout << queryStr << "   no alternatives found"<< endl;
				}
		}
	/* close the stream*/
	queries.close();

	return 0;
}
