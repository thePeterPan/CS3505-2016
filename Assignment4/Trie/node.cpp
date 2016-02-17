/* 
 * File:    node.cpp
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#include <algorithm>

#include "node.h"

/**
 * Constructor
 */
node::node(char value)
    : value(value), child_nodes(), word_flag(false)
{
    ++refCount;
}

/**
 * Destructor
 */
node::~node() {    
    for (int i = 0; i < child_nodes_array_size; i++ ) {
        delete child_nodes[i];
        --refCount;
    }
}

/**
 * Copy Constructor
 * @param orig
 */
node::node(const node& original)
      : value(original.value), 
        child_nodes(), 
        list_of_children(original.list_of_children),
        word_flag(original.word_flag)
{
    std::copy(original.child_nodes, original.child_nodes + original.child_nodes_array_size, child_nodes);
}

/**
 * 
 * https://en.wikipedia.org/wiki/Assignment_operator_(C%2B%2B)#Overloading_copy_assignment_operator
 * 
 * @param other
 * @return  
 */
node& node::operator =(const node& other) {
    
    // protect against invalid self-assignment
    if (this != &other) {
        // 1: Allocate new memory and copy the elements
        node* copied_child_nodes[child_nodes_array_size];
        std::copy(other.child_nodes, other.child_nodes + other.child_nodes_array_size, copied_child_nodes);
        
        // 2: deallocate old memory, same code as destructor
        for (int i = 0; i < child_nodes_array_size; i++ ) {
            delete child_nodes[i];
        }
        
        // 3: assign the new objects
//        child_nodes = copied_child_nodes;
        value = other.value;
        list_of_children = other.list_of_children;
        word_flag = other.word_flag;
    }
    
    // by convention, always return *this
    return *this;
}

/**
 * Get the value of the current node
 * 
 * @return the value of the current node
 */
char node::getValue() {
    return value;
}

/**
 * 
 * @param index
 * @param node
 */
void node::addChildNode(char character) {
    // If the character is an invalid character, quit.
    if (int(character) > 122 || int(character) < 97)
        return;
    
    // Get the index at which to store the character (i.e. hashing it)
    int charIndex = int(character) - 97;
    
    // Check to see if this character already exits
    if (child_nodes[charIndex] != nullptr) {
        // if it does, just quit.
        return;
    }
    
    // Otherwise, create a new node and add it to the array. 
    child_nodes[charIndex] = new node(character);
    // and add child to list of children
    list_of_children.push_back(character);
}

/**
 * Gets the child node a the specified index.
 * 
 * @param index - the location of the child node.
 * @return the child node. 
 */
node* node::getChildNode(char character) {
    if (int(character) > 122 || int(character) < 97)
        return nullptr;
    int charIndex = int(character) - 97;
    return child_nodes[charIndex];
}

/**
 * If an invalid character is given, instead of being clamped, false is given.
 * 
 * @param character
 * @return 
 */
bool node::childNodeExists(char character) {
    if (int(character) > 122 || int(character) < 97)
        return false;
    
    // Get the index at which the character should be stored.
    int charIndex = int(character) - 97;
    if (child_nodes[charIndex] != nullptr) {
        return true;
    }
    return false;
}

/**
 * 
 * @return 
 */
std::vector<char> node::getListOfChildren() {
    return list_of_children;
}

/**
 * This method is used to determine if the current node 
 * is the ending of a word. Even if the node has children, it could
 * still be a word.
 * 
 * @param isWord
 */
void node::setWordFlag(bool isWord) {
    word_flag = isWord;
}

bool node::getWordFlagState() {
    return word_flag;
}