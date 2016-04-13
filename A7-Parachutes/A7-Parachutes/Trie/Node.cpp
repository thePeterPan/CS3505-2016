//TrieTest written by Kevin Griggs Feb. 7, 2016
// U0663183

#include <iostream>
#include "Node.h"
using namespace std;


//an array of pointers to other nodes...
Node::Node()
{
	isRealWord = false;
	for (int i = 0; i < 26; i++)
	{
		nodePointerArr[i] = 0;
	}
	
}

Node* Node::getChild(int index)
{
	return nodePointerArr[index];
}
