//TrieTest written by Kevin Griggs Feb. 7, 2016
// U0663183

#include <vector>
#include "Node.h"
#include <string>

#ifndef _INCL_GUARD
using namespace std;

extern int refCount;


class Trie {
private:
	Node rootNode;
	char getCharFromIndex(int index);
	int getIndexFromChar(char ch);
	Node* getToNode(Node* currentNode, string word);
	void allWordsInNode(string tempString, vector<string>* wordVector, Node* nodePointer);
	void traverseDeleteRecursion(Node* root);
	void traverseCopyRecursion(Node* currentNode, const Node* otherRoot);
public:
	Trie();
	~Trie();
	Trie(const Trie& other);
	Trie& operator=(Trie& other);
	void addWord(string newWord);
	bool isWord(string possibleWord);
	vector<string> allWordsWithPrefix(string prefix);
	friend void swap(Trie& first, Trie& second);

};
#endif
