/* 
 * File:   node.h
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#ifndef NODE_H
#define NODE_H

#include <vector>

template<typename kind>
class node {
    
public:
    // Constructor
    node(size_t numberOfChildren);
    // Copy Constructor    
    node(const node& orig);
    // Destructor
    virtual ~node();
    
    /**
     * Get the value of the current node
     * @return the value of the current node.
     */
    kind getValue();
    
private:
    
    kind value;
    
    // vector of pointers for child nodes
    // May want to change this to array or another data type
    std::vector<node *> children;

    node *childNodes[26];
};

#endif /* NODE_H */

