//TrieTest written by Kevin Griggs Feb. 7, 2016
// U0663183

#include <iostream>
#include <string>
#include "Trie.h"

using namespace std;

//default constructor
Trie::Trie()
{
	
}

//destructor
Trie::~Trie()
{
	//delete each node in the trie
	//I think I just need to go through the trie and delete? each Node
	traverseDeleteRecursion(&rootNode);
}

//copy constructor
Trie::Trie(const Trie& other)
{

	traverseCopyRecursion(&rootNode, &other.rootNode);

	rootNode = other.rootNode;
	//this is where you go through and perform a deep copy of each node
}

//assignment operator override
Trie& Trie::operator=(Trie& other)
{
	//I got this line from stackoverflow and from the slides in class
	swap(*this, other);
	return *this;
}


void Trie::addWord(string newWord)
{
	//this could be in the node class, and a helper method is called in the 
	Node* currentNode = &rootNode;
	for (unsigned int i = 0; i < newWord.size(); i++)
	{
		int index = getIndexFromChar(newWord[i]);
		if (currentNode->getChild(index) == nullptr)
		{
			//add new Node
			currentNode->nodePointerArr[index] = new Node();
			currentNode = currentNode->nodePointerArr[index];
		}
		else 
			currentNode = currentNode->nodePointerArr[index];

	}
	currentNode->isRealWord = true;
}

bool Trie::isWord(string possibleWord)
{
	Node* currentNode = &rootNode;
	
	for (unsigned int i = 0; i < possibleWord.size(); i++)
	{
		int index = getIndexFromChar(possibleWord[i]);
		if (currentNode->getChild(index) == nullptr)
			return false;
		else
		{
			currentNode = currentNode->getChild(index);
		}
	}
	
	if (currentNode->isRealWord)
		return true;
	else return false;
}

vector<string> Trie::allWordsWithPrefix(string prefix)
{
	Node* currentNode = &rootNode;

	for (unsigned int i = 0; i < prefix.size(); i++)
	{
		int index = getIndexFromChar(prefix[i]);
		if (currentNode->getChild(index) == nullptr)
			return vector<string>();
		else
		{
			currentNode = currentNode->getChild(index);
		}
	}
	vector<string>* vec = new vector<string>;

	if (currentNode->isRealWord)
		vec->push_back(prefix);

	allWordsInNode(prefix, vec, currentNode);
	return *vec;
}

char Trie::getCharFromIndex(int index)
{
	return (char)(index + 97);
}

int Trie::getIndexFromChar(char ch)
{
	return (int)ch - 97;
}

Node* Trie::getToNode(Node* currentNode, string word)
{
	for (unsigned int i = 0; i < word.size(); i++)
	{
		int index = getIndexFromChar(word[i]);
		if (currentNode->getChild(index) == nullptr)
			return nullptr;
		else
		{
			currentNode = currentNode->getChild(index);
		}
	}
	return currentNode;
}

void Trie::allWordsInNode(string tempString, vector<string>* wordVector, Node* currentNode)
{
	Node* childNode;
	//check to see if any of the pointers in the nodePointerArray are not null,
	//if they aren't null, then the base case has not been reached and the recursion must continue.	
	for (int i = 0; i < 26; i++)
	{
		if (currentNode->nodePointerArr[i] != nullptr)
		{
			childNode = currentNode->getChild(i);

			tempString = tempString + getCharFromIndex(i);
			if (childNode->isRealWord)
				wordVector->push_back(tempString);
			allWordsInNode(tempString, wordVector, childNode);
			//to be honest, I'm not really sure why I have to do this, but I saw someone do it on
			//stackoverflow and it solved my problems.
			tempString.pop_back();
		}	
	}
}

void Trie::traverseDeleteRecursion(Node* currentNode)
{
	Node* childNode;
	//check to see if any of the pointers in the nodePointerArray are not null,
	//if they aren't null, then the base case has not been reached and the recursion must continue.	
	for (int i = 0; i < 26; i++)
	{
		if (currentNode->nodePointerArr[i] != nullptr)
		{
			childNode = currentNode->getChild(i);
			traverseDeleteRecursion(childNode);
			delete childNode;
		}

	}
}


void Trie::traverseCopyRecursion(Node* currentNode, const Node* otherCurrent)
{
	Node* childNode;
	//Node* otherChildNode;
	//check to see if any of the pointers in the nodePointerArray are not null,
	//if they aren't null, then the base case has not been reached and the recursion must continue.	
	for (int i = 0; i < 26; i++)
	{
		if (otherCurrent->nodePointerArr[i] != nullptr)
		{
			childNode = otherCurrent->nodePointerArr[i];

			traverseCopyRecursion(childNode, currentNode);
			currentNode = new Node();
			currentNode = childNode;

		}

	}
}
void swap(Trie& first, Trie & second) // nothrow
{
	// enable ADL (not necessary in our case, but good practice)
	using std::swap;

	// by swapping the members of two classes,
	// the two classes are effectively swapped
	swap(first.rootNode, second.rootNode);
}
