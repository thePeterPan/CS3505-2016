#ifndef TRIE_H
#define TRIE_H
#include <vector>
#include <string>
#include "Node.h"
using namespace std; 
class Trie
{
     private :
          Node* root;
          bool flag;
          
     public :
  
   		  Trie();
   		    ~Trie(); // Destructor
   		    Trie(const Trie& other);
   			Trie & operator=(Trie other);
          void addWord(std::string s);
          //A method addWord that accepts a std::string and returns void. 
          //compare two time object
          bool isWord(std::string s);
          std::vector<std::string>  allWordsWithPrefix(std::string s);
          void findchildren(Node* current, std::vector<string>& result, string s);


};
 
#endif
