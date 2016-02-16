/* 
 * File:   node.h
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 * Notes: 
 * http://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
 */

#ifndef NODE_H
#define NODE_H

#include <vector>       // std::vector<type>
#include <cstdint>      // std::size_t

// Put the extern int refCount in any header whose .cpp needs to use it
// since it is a declaration of the refCount variable not definition.
extern int refCount;

class node {

public:

    static const int child_nodes_array_size = 26;

    // Constructor
    node(char value);
    // Destructor
    virtual ~node();
    // Copy Constructor    
    node(const node& orig);
     
    /**
     * 
     * 
     * @param other
     * @return 
     */
    node& operator =(const node& other);
    
    /**
     * Get the value of the current node
     * 
     * @return the value of the current node.
     */
    char getValue();
    
    /**
     * 
     * @param index
     * @param node
     */
    void addChildNode(char character);
    
    /**
     * Gets the child node a the specified index.
     * 
     * @param index - the location of the child node.
     * @return the child node. 
     */
    node* getChildNode(char character);
    
    /**
     * 
     * @param character
     * @return 
     */
    bool childNodeExists(char character);
    
    /**
     * 
     * @return 
     */
    std::vector<char> getListOfChildren();
    
    /**
     * This method is used to determine if the current node 
     * is the ending of a word. Even if the node has children, it could
     * still be a word.
     * 
     * @param isWord
     */
    void setWordFlag(bool isWord);
    bool getWordFlagState();
    
private:
    
    char value;
    
    // vector of pointers for child nodes
    // May want to change this to array or another data type
    node* child_nodes[child_nodes_array_size];
    
    // List of all the children in the node
    std::vector<char> list_of_children;
    
    // If the current node is the end of a word.
    bool word_flag;
};

#endif /* NODE_H */
