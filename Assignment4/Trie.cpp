/* 
 * File:    Trie.cpp
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#include "Trie.h"

#include <algorithm>        // std::remove

/**
 * Default Constructor
 */
Trie::Trie()
    : rootNode('0') { }

/**
 * Destructor
 */
Trie::~Trie() {
    // handled in the node class
}

/**
 * Copy Constructor
 * 
 * @param orig - 
 */
Trie::Trie(const Trie& orig) 
    : rootNode(orig.rootNode)
{
    
}

/*
 * Assignment operator overload.
 * 
 * @param rhs - 
 * @return 
 */
Trie& Trie::operator =(const Trie& rhs) {
    
    // protect against invalid self-assignment
    if (this != &rhs) {
        // the rest of the work should be handled by the node class.
        rootNode = rhs.rootNode;
    }    
    // by convention, always return *this
    return *this;
}

/**
 * Accepts a std::string and returns void. The word passed into the method 
 * should be added to the Trie. Duplicate adds should not change the Trie. 
 * You may assume that the word is only made up of lower-case characters 
 * from a-z.
 * 
 * @param word - the word to add to the Trie.
 */
void Trie::addWord(std::string word) {
    // Remove the word of any excess newlines just in case.
    std::string clean_word(trimWord(word));
    
    // If we received an empty word, just quit.
    if (clean_word.length() == 0) 
        return;
    
    // Starting pointer
    node* ptr_current_node = &rootNode;
    
    // Loop through the word pulling out individual characters and inserting
    // them into the trie.
    for (unsigned i = 0; i < clean_word.length(); i++) {
        // if the character does not exist
        if (!ptr_current_node->childNodeExists(clean_word.at(i))) {
            // add the character to the trie
            ptr_current_node->addChildNode(clean_word.at(i));
        }
        // otherwise, move to the next node
        ptr_current_node = ptr_current_node->getChildNode(clean_word.at(i));
    }
    
    // Since we are at the end of the word, we want to flag the node as
    // the end of a word.
    ptr_current_node->setWordFlag(true);
}

/**
 * Accepts a std::string and returns bool. The argument is a word made up 
 * of characters 'a'-'z'. If the word is found in the Trie, the method 
 * should return true, otherwise return false.
 * 
 * @param word - the word to look up.
 * @return true if the word is found in the trie.
 */
bool Trie::isWord(std::string word) {
    // Remove the word of any excess newlines just in case.
    std::string clean_word(trimWord(word));
    
    // If we received an empty word return false.
    if (clean_word.length() == 0) 
        return false;
    
    // Starting pointer
    node* ptr_current_node = &rootNode;
    
    for (unsigned i = 0; i < clean_word.length(); i++) {
        if (!ptr_current_node->childNodeExists(clean_word.at(i))) {
            // if at any point the character does not exist, return false.
            return false;
        }
        // move to the next node
        ptr_current_node = ptr_current_node->getChildNode(clean_word.at(i));
    }
    // If we've looped through the entire word, several checks need to be made.
    if (ptr_current_node->getWordFlagState() || ptr_current_node->getListOfChildren().size() == 0) {
        // If the word flag is true or if the node has no children, then it is
        // a word.
        return true;
    }
    // Otherwise, even if it is the end of the word, it's not necessarily a
    // word that was placed in the trie. 
    return false;
}

/**
 * Accepts a std::string and returns a vector<std::string> that contains 
 * all the words in the Trie that start with the passed in argument 
 * prefix string. A word that is just the prefix is acceptable. An empty 
 * prefix should return all words in the Trie.
 * 
 * @param prefix - the word.
 * @return a vector string with all the words in the trie that start with
 *      the passed in argument.
 */
std::vector<std::string> Trie::allWordsWithPrefix(std::string prefix) {
    // Remove the word of any excess newlines just in case.
    std::string clean_word(trimWord(prefix));
    
    std::vector<std::string> words_with_prefix;
    
    node* ptr_current_node = &rootNode;
    for (unsigned i = 0; i < clean_word.length(); i++) {
        if (!ptr_current_node->childNodeExists(clean_word.at(i))) {
            // if at any point the character does not exist, that means 
            // there aren't any word with that prefix. Return an empty vector.
            return words_with_prefix;
        }
        // otherwise, move to the next node
        ptr_current_node = ptr_current_node->getChildNode(clean_word.at(i));
    }
    
    // Use recursion to traverse the remainder of the Trie.
    addPrefixesToVector(words_with_prefix, ptr_current_node, clean_word);
    
    return words_with_prefix;
}

/**
 * Use recursion to traverse the Trie starting from the end of the given
 * prefix. Once the traversal has reached a child that does not have its own
 * children, then it has reached the end meaning that is a word that it can
 * add to the list of words that contain the given prefix. 
 * 
 * @param words_with_prefix - The list of words with the prefix to add to
 * @param current_node_pointer - A pointer to the current node in the recursion.
 * @param word - The partial word to append characters to that will eventually
 *      be added to the words_with_prefix vector when it reaches the leaf of the
 *      Trie. 
 */
void Trie::addPrefixesToVector(
        std::vector<std::string>& words_with_prefix, 
        node* current_node_pointer, 
        std::string word)
{
    std::vector<char> list_of_children = current_node_pointer->getListOfChildren();
    
    // If it is a word based on the flag state
    if (current_node_pointer->getWordFlagState()) {
        words_with_prefix.push_back(word);
    }   
    
    // Define the base case: when the child has no children of its own.
    if (list_of_children.size() == 0) {
        return;
    }
    
    // If there are children, loop through all of them to recurse through them.
    std::vector<char>::iterator it; 
    for (it = list_of_children.begin(); it < list_of_children.end(); it++) 
    {
        addPrefixesToVector(
                words_with_prefix, 
                current_node_pointer->getChildNode(*it), 
                word + current_node_pointer->getChildNode(*it)->getValue());
    }
}

/**
 * Removes any excess newline characters etc.
 * 
 * @param word
 * @return 
 */
std::string Trie::trimWord(std::string word) {
    std::string clean_word = word;
    clean_word.erase(std::remove(clean_word.begin(), clean_word.end(), '\n'), clean_word.end());
    clean_word.erase(std::remove(clean_word.begin(), clean_word.end(), '\r'), clean_word.end());
    return clean_word;
}
