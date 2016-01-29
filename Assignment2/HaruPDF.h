/*
 * Peter Pan
 * u0680482
 * CS3505
 * Assignment 2 
 * 
 * Header file for HaruPDF facade class
 */

#ifndef HARUPDF_H
#define HARUPDF_H

#include <iostream>
#include <string>
#include "hpdf.h"       // HPDF_Doc, HPDF_Page, HPDF_Font

class HaruPDF {
    
private: 
    
    HPDF_Doc    pdf;
    HPDF_Page   page;
    HPDF_Font   font;
    
public: 
    
    /**
     * Default Constructor
     */
    HaruPDF() {}
    
    /**
     * Destructor
     */
    ~HaruPDF();
    
    /**
     * 
     * @param character
     */
    void insert_char(char character);
    
    /**
     * 
     * @param filename
     * @return 
     */
    bool save_pdf(std::string filename);
};

#endif