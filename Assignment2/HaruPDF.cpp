/*
 * Peter Pan
 * u0680482
 * CS3505
 * Assignment 2 
 * 
 * HaruPDF facade class.
 * General purpose for placing text on a page and saving the pdf.
 */

#include "HaruPDF.h"    // Header file
#include <iostream>
#include "hpdf.h"       // HPDF_New, 
#include <cmath>        // cos, sin

using namespace std;

/**
 * Default Constructor
 */
HaruPDF::HaruPDF() {
    // Create a new pdf document
    pdf = HPDF_New(NULL, NULL);
    // Add a new page to the document
    page = HPDF_AddPage(pdf);
    // Set the size of the page to A5 size in portrait orientation
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
    // Set a default font to Helvetica
    font = HPDF_GetFont(pdf, "Helvetica", NULL);
    
    // Sets the text leading (line spacing) for text showing
    HPDF_Page_SetTextLeading(page, 20);
    // Sets the stroking color
    HPDF_Page_SetGrayStroke(page, 0);
    
    // Begins a text object and sets the text position to (0, 0).
    HPDF_Page_BeginText(page);
    // Sets the type of font and size leading
    HPDF_Page_SetFontAndSize(page, font, 30);
}

/**
 * Destructor
 */
HaruPDF::~HaruPDF() {
    
}

/**
 * 
 * @param character
 * @param letterAngle
 * @param xPos
 * @param yPos
 */
void HaruPDF::insert_char(char character, double letterAngle, double xPos, double yPos) {
    
    
    //page - The handle of a page object
    //a - The horizontal rotation of the text. Typically expressed as cosine(Angle)
    //b - The vertical rotation of the text. Typically expressed as sine(Angle)
    //c, d - ?? Appear to be controlling offset adjustments after text drawn ???
    //x - The page x coordinate
    //y - The page y coordinate
    
    HPDF_Page_SetTextMatrix(page, 
            cos(letterAngle), sin(letterAngle), 
            -sin(letterAngle), cos(letterAngle), 
            xPos, yPos);
    
    char buffer[2];
    buffer[0] = character;
    buffer[1] = 0;
    HPDF_Page_ShowText(page, buffer);   
}

void HaruPDF::save_pdf(const char* filename) {
    
    HPDF_Page_EndText(page);
    HPDF_SaveToFile(pdf, filename);
    HPDF_Free(pdf);
}
