/* 
 * File:    node.cpp
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#include "node.h"

/**
 * Constructor
 */
template<class kind>
node<kind>::node(kind value)
    : value(value)
{
    
}

/**
 * Copy Constructor
 * @param orig
 */
template<class kind>
node<kind>::node(const node& orig) {
    
}

/**
 * Destructor
 */
template<class kind>
node<kind>::~node() {
    
}

/**
 * Get the value of the current node
 * @return the value of the current node
 */
template<class kind>
kind node<kind>::getValue() {
    return value;
}

/**
 * 
 * @param index
 * @param node
 */
template<class kind>
void node<kind>::addChildNode(int index, node<kind> node) {
    childCount++;
}

/**
 * Gets the child node a the specified index.
 * @param index - the location of the child node.
 * @return the child node. 
 */
template<class kind>
node<kind> node<kind>::getChildNode(int index) {
    return childNodes[index];
}

/**
 * Returns true if this node has no children.
 * @return true if no children, false otherwise.
 */
template<class kind>
bool node<kind>::noChildren() {
    return childCount == 0;
}