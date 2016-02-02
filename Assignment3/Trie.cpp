/* 
 * File:    Trie.cpp
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#include "Trie.h"

/**
 * Constructor
 */
Trie::Trie() {
    
}

/**
 * Copy Constructor
 * 
 * @param orig - 
 */
Trie::Trie(const Trie& orig) {
//    this->value(orig.value);
}

/**
 * Destructor
 */
Trie::~Trie() {
    
}

/**
 * Assignment operator overload.
 * 
 * @param rhs - 
 * @return 
 */
Trie& Trie::operator =(const Trie &rhs) {
    // this->value = rhs.value;
    return (*this);
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
    return std::vector<std::string>();
}

