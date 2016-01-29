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
#include "hpdf.h"       // HPDF_*
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
 * Inserts the given character into the document at the given position.
 * @param character
 * @param letterAngle
 * @param xPos
 * @param yPos
 */
void HaruPDF::insert_char(char character, double letterAngle, double xPos, double yPos) {
    
    // HPDF_Page_SetTextMatrix(HPDF_Page page, HPDF_REAL a, HPDF_REAL b, HPDF_REAL c, HPDF_REAL d, HPDF_REAL x, HPDF_REAL y)
    // Sets a transformation matrix for text to be drawn in using HPDF_Page_ShowText().
    // page - The handle of a page object
    // a - The horizontal rotation of the text. Typically expressed as cosine(Angle)
    // b - The vertical rotation of the text. Typically expressed as sine(Angle)
    // c, d - ?? Appear to be controlling offset adjustments after text drawn ???
    // x - The page x coordinate
    // y - The page y coordinate
    HPDF_Page_SetTextMatrix(page, 
            cos(letterAngle), sin(letterAngle), 
            -sin(letterAngle), cos(letterAngle), 
            xPos, yPos);
    
    // C-style strings are null-terminated. The last character must a 0.
    char buffer[2];
    buffer[0] = character;
    buffer[1] = 0;
    
    // Print the text at the current position on the page
    HPDF_Page_ShowText(page, buffer);   
}

/**
 * 
 * @param filename
 */
void HaruPDF::save_pdf(const char* filename) {
    // End the text object
    HPDF_Page_EndText(page);
    // Save the current document to the specified file
    HPDF_SaveToFile(pdf, filename);
    // Revoke the document object and all resources
    HPDF_Free(pdf);
}
