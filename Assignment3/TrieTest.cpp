/* 
 * File:    TrieTest.cpp
 * Author:  Peter Pan
 * Uid:     u0680482
 * Class:   CS3505
 *          Assignment 3
 *
 */

#include <cstdlib>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>       // std::string, std::getline

#include "Trie.h"
#include "node.h"

using namespace std;

/**
 * Check to see if a file exists.
 * @param name - the path to the file.
 * @return true if the file exists, false otherwise.
 */
bool file_exists(const std::string& name) {
    std::ifstream file(name.c_str());
    if (file.good()) {
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }   
}

/**
 * 
 * @param argc - the number of arguments passed to the program plus the current
 *               executing file. 
 * @param argv - argv are the command line arguments, argv[0] is the name of the
 *               executable program, argv[1] is the first argument. 
 * @return 
 */
int main(int argc, char** argv) {

    // Make sure that there is a valid number of arguments.
    // If you want to be sure a concatenation chain will work, just make sure one of the first two arguments is explicitly of type std::string
    // http://stackoverflow.com/questions/23936246/error-invalid-operands-of-types-const-char-35-and-const-char-2-to-binar
    std::string errorText = std::string("Expecting two arguments: The first is a file of ") +
            "words, each on their own line, with the words all lowercase and " +
            "only made up of characters a-z. The second is a file of queries, " +
            "each word on its own line and also of acceptable characters.";
    if (argc < 3) {
        std::cout << errorText << std::endl;
        return 1;
    } else if (argc > 3) {
        std::cout << "Too many arguments! " << errorText << std::endl;
        return 1;
    }
    
    if (!file_exists(argv[1])) {
        std::cout << "The following file does not exist: " << argv[1] << std::endl;
        return 1;
    } else if (!file_exists(argv[2])) {
        std::cout << "The following file does not exist: " << argv[2] << std::endl;
        return 1;
    }
    
    Trie mainTrie;
    
    // Collect all the words in the dictionary file and store it in the trie
    std::ifstream dictionaryFile(argv[1]);
    while (!dictionaryFile.eof()) {
        // initialize a variable to hold the current line
        std::string currentWord;
        // get the line and store the word
        std::getline(dictionaryFile, currentWord);
        // add the word to the trie
        mainTrie.addWord(currentWord);
    }
    // Close the file handle
    dictionaryFile.close();

    
    // Perform a query search for each word in the query file
    std::ifstream queriesFile(argv[2]);
    while (!queriesFile.eof()) {
        // initialize a variable to hold the current line
        std::string currentWord;
        // get the line and store the word
        std::getline(queriesFile, currentWord);
//        std::cout << "Current Word: " << currentWord << endl;
        
        // Check to see if the queried word exists in the trie
        if (mainTrie.isWord(currentWord)) {
            // If it exists print the appropriate message
            std::cout << std::string(currentWord) + " is found" << endl;
        } else {
            // Otherwise get a list of alternative words if there are any
            std::vector<std::string> alternatives(mainTrie.allWordsWithPrefix(currentWord));
            
            if (alternatives.size() == 0) {                
                // If there aren't any alternatives, print message
                std::cout << "no alternatives found" << endl;
            } else {
                // Otherwise suggest alternative words
                std::cout << std::string(currentWord) + " is not found, did you mean:" << endl;
                // and print them out
                // create a new vector iterator
                std::vector<std::string>::iterator it;
                // loop through the iterator, printing out the alternatives
                for (it = alternatives.begin(); it < alternatives.end(); it++) {
                    std::cout << *it << endl;
                }
            }
        }
    }
    queriesFile.close();
    
//    // create a new vector iterator
    std::vector<std::string>::iterator it;
    vector<string> myvector;
        myvector.push_back("a");
        myvector.push_back("b");
        myvector.push_back("c");
        myvector.push_back("d");

    for (it = myvector.begin(); it < myvector.end(); it++) {
        std::cout << *it << endl;
    }
    
    return 0;
}
