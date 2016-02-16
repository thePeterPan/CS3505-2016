#ifndef NODE_H
#define NODE_H

class Node {

private:
	bool _isEnd;
	Node* word[26]; 

public:
	Node();


	Node(const Node& other);


	~Node();


	void setEnd();


	bool isEnd();


	Node** getword();
};

#endif