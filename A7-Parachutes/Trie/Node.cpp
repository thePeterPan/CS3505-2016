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

//char value;
//default constructor
/*
Node()
{
//nodes contain an array of 26 pointers to more nodes
for (int i = 0; i < 25; i++)
{
nodePointer[i] = nullptr;
}
//value =
isRealWord = false;
}

Node* current ()
{
//return
}
*/
