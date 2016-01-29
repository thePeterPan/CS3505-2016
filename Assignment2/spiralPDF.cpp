/*
 * Peter Pan
 * u0680482
 * CS3505
 * Assignment 2 
 * 
 * Testing class
 */

#include <iostream>     // std::cout
#include <cstring>      // std::strcpy, std::strcat
#include "HaruPDF.h"    // 
#include "Spiral.h"     // 

using namespace std;

/**
 * 
 * @param argc - the number of arguments passed to the program plus the current
 *               executing file. 
 * @param argv - argv are the command line arguments, argv[0] is the name of the
 *               executable program. 
 * @return 
 */
int main(int argc, char **argv)
{
    // Set the name of the output file: 
    char file_name[256];
    std::strcpy(file_name, argv[0]);
    std::strcat(file_name, ".pdf");
    
    
    // Make sure that there is a valid number of arguments. 
    if (argc < 2) {
        std::cout << "Please provide sample text!" << endl;
        return 1;
    } else if (argc > 2) {
        std::cout << "Too many arguments!" << endl;
        return 1;
    }
    
    
    unsigned int i;
    const char* sampleText = argv[1];
    Spiral spiral1();
    
    for (i = 0; i < std::strlen(sampleText); i++) {
        std::cout << sampleText[i] << endl;
    }
    
    return 0;
}
