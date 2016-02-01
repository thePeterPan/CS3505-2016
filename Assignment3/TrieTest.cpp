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
#include <string>       // std::string
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
        std::cout << "File does not exist: " << argv[1] << std::endl;
        return 0;
    } else if (!file_exists(argv[2])) {
        std::cout << "File does not exist: " << argv[2] << std::endl;
        return 0;
    }
    
    return 0;
}

