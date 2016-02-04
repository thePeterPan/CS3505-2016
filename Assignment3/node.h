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

#include <vector>
#include <cstdint>      // std::size_t

template<class kind> 
class node {
    
public:
    // Constructor
    node(kind value);
    // Copy Constructor    
    node(const node& orig);
    // Destructor
    virtual ~node();
    
    /**
     * Get the value of the current node
     * @return the value of the current node.
     */
    kind getValue();
    
    /**
     * 
     * @param index
     * @param node
     */
    void addChildNode(int index, node<kind> node);
    
    /**
     * Gets the child node a the specified index.
     * @param index - the location of the child node.
     * @return the child node. 
     */
    node<kind> getChildNode(int index);
    
    /**
     * Returns true if this node has no children.
     * @return true if no children, false otherwise.
     */
    bool noChildren();
    
private:
    
    kind value;
    
    // vector of pointers for child nodes
    // May want to change this to array or another data type
    std::vector<node *> childNodes;
    
    // Counts number of children in the node
    int childCount = 0;
};

#endif /* NODE_H */

