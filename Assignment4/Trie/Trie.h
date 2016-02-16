/* 
 * File:    Trie.h
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#ifndef TRIE_H
#define TRIE_H

#include <string>       // std::string
#include <vector>       // std::vector

#include "node.h"       // node

// Put the extern int refCount in any header whose .cpp needs to use it
// since it is a declaration of the refCount variable not definition
extern int refCount;

class Trie {
    
public:

    // Default Constructor
    Trie();
    // Destructor
    virtual ~Trie();
    // Copy Constructor
    Trie(const Trie& orig);
    
    /**
     * Assignment operator overload
     * 
     * @param rhs
     * @return 
     */
    Trie& operator=(const Trie& rhs);
    
    /**
     * Accepts a std::string and returns void. The word passed into the method 
     * should be added to the Trie. Duplicate adds should not change the Trie. 
     * You may assume that the word is only made up of lower-case characters 
     * from a-z.
     * 
     * @param word - the word to add to the Trie.
     */
    void addWord(std::string word);
    
    /**
     * Accepts a std::string and returns bool. The argument is a word made up 
     * of characters 'a'-'z'. If the word is found in the Trie, the method 
     * should return true, otherwise return false.
     * 
     * @param word - the word to look up.
     * @return true if the word is found in the trie.
     */
    bool isWord(std::string  word);
    
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
    std::vector<std::string> allWordsWithPrefix(std::string prefix);
    
private:
    
    // Holds the root node of the trie.
    node rootNode;
    
    /**
     * Removes any excess newline characters etc.
     * 
     * @param word
     * @return 
     */
    std::string trimWord(std::string word);
    
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
    void addPrefixesToVector(
        std::vector<std::string>& words_with_prefix, 
        node* current_node_pointer, 
        std::string word);
};

#endif /* TRIE_H */

