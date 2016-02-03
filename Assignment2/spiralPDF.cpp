/*
 * Peter Pan
 * u0680482
 * CS3505
 * Assignment 2 
 * 
 * Testing class
 */

#define _CRT_SECURE_NO_WARNINGS

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
    
    
    // Store the text passed in from the command line    
    const char* sampleText = argv[1];
    // Create a new spiral object to control text position
    Spiral spiral1(210, 300, 0, 50);
    // Create a facade class to interface with libHaru
    HaruPDF haruPdf1;
    
    // Loop through each character in the text, printing it onto
    // the pdf document. 
    unsigned int index;
    for (index = 0; index < std::strlen(sampleText); index++) {
        haruPdf1.insert_char(
                sampleText[index], 
                spiral1.get_text_angle(),
                spiral1.get_text_x(),
                spiral1.get_text_y()
                );
        spiral1++;
    }
    
    // Save and close the pdf file.
    haruPdf1.save_pdf(file_name);
    
    return 0;
}
