#include "Node.h"
extern int refCount;
Node::Node() : _isEnd(false) { 

for (unsigned i = 0; i < 26; i ++)
		word[i] = 0;
	
}
//constructor for copy with other
Node::Node(const Node& other) : _isEnd(other._isEnd) {
for (unsigned i = 0; i < 26; i ++)
		if(other.word[i])
			word[i] = new Node(*(other.word[i]));
}
//deconstructor for deleting node
Node::~Node() {
for (unsigned i = 0; i < 26; i++)
		while(this->word[i])
			{
			refCount=refCount-1;
			delete this->word[i];
			}
			
}

// helper for vaild node 
void Node::setEnd() {
	_isEnd = true;
}

// helper for valid node 
bool Node::isEnd() {
	return _isEnd;
}

// helper for get current chars
Node** Node::getword() {
	return word;
}

