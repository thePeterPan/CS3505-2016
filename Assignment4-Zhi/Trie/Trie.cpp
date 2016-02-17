#include <iostream>
#include <iomanip>
#include "Trie.h"
#include <vector>
using namespace std;
 
 extern int refCount;
Trie::Trie()
{

 root = new Node();   
} // Constructor
  
  //copy
 Trie::Trie(const Trie& other) {
	root = new Node(*(other.root));	// copy the root from other
} 
Trie::~Trie () {
delete root;
refCount==0;
  //delete root;
}
Trie& Trie::operator=(Trie other)
{
	if(this == &other)
		{
			return *this;
		}
		std::swap(root,other.root);
		return *this;
	}
 
void Trie :: addWord(string s) 
{
         refCount++;
		if(s.length() == 0)
		{
			return;
		}
		Node* current = root;
		for(unsigned i = 0; i < s.length(); i++) {
    	char letter = s[i];
    	int Index = letter - 'a';
    	if(!current->getword()[Index])
    		current->getword()[Index] = new Node();
    	current = current->getword()[Index];
	}
	current->setEnd();
         
         
         
}		
 

 
bool Trie :: isWord(string s)
{
    if(s.length() == 0)
		{
			return false;
		}
		Node* current = root;
		
		
for(unsigned i = 0; i < s.length(); i++) {

		char letter = s[i];
    	int Index = letter - 'a';
    	if(!current->getword()[Index])
    		return false;
    	current = current->getword()[Index];
}

	return current->isEnd(); 
		
}

vector<string> Trie::allWordsWithPrefix(string s) {
Node* current = root;
	for(unsigned i = 0; i < s.length(); i++) {
	
	char letter = s[i];
    	int Index = letter - 'a';
    	/* return an empty vector if the prefix is not on the Trie*/
    	if(!current->getword()[Index])
    		return vector<string>();
    	/* go to the next child*/
    	current = current->getword()[Index];
	
	
	
	}

vector<string> result;
	Trie::findchildren(current, result, s);
	return result;



}
void Trie::findchildren(Node* current, vector<string>& result, string s) {
	/* if current points to an end of a word, push the prefix to the vector*/
	if(current->isEnd())
		result.push_back(s);
	/* iterate the valid node, recursively call this function giving arguments corresponding with the child node*/
	for(unsigned i = 0; i < 26; i++)
		if(current->getword()[i])
			findchildren(current->getword()[i], result, s + (char)(i + 'a'));	
}









