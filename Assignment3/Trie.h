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

class Trie {
    
public:
    
    // Constructor
    Trie();
    
    // Copy Constructor
    Trie(const Trie& orig);
    
    // Destructor
    virtual ~Trie();
    
    // Assignment operator overload
    Trie& operator=(const Trie &rhs);
    
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

};

#endif /* TRIE_H */

