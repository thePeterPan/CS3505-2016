/*
 * Peter Pan
 * u0680482
 * CS3505
 * Assignment 2 
 * 
 * Header file for Spiral class
 */


/* #ifndef checks whether the given token has been #defined earlier in the file 
 * or in an included file; if not, it includes the code between it and the 
 * closing #else or, if no #else is present, #endif statement. 
 */
#ifndef SPIRAL_H
#define SPIRAL_H

// Sometimes this is needed in older versions/Visual C++
#define _USE_MATH_DEFINES

#include <iostream>     // std::ostream
#include <cmath>        // M_PI

class Spiral {
    
    // Center X coordinate
    double centerX;
    // Center Y coordinate
    double centerY;
    
    // Degrees which gives the starting angle clockwise from vertical 
    // for the text to begin drawing
    double angle;
    
    // The spiral should grow larger from this start size.
    double startingRadius;
    
public: 
    
    // Constructor: 
    Spiral(double centerX, double centerY, double angle, double startingRadius);
    
    // Destructor: 
    ~Spiral();
    
    /* 
     * Overloading the increment (++) operator: 
     * 
     * Advances the spiral to its next position. The next position should be 
     * suitable for the next character of the text to be placed. This next 
     * position should be pleasing: text should not overlap or be too spread 
     * out and the lines should have some spacing. This pleasant spacing should 
     * at least work for spirals that fit on one 8.5 x 11in page.
     */
    Spiral operator++(int);     // Postfix increment operator.
    Spiral& operator++();       // Prefix increment operator. 
    
    // Gets the x coordinate for the text position
    double get_text_x();
    // Gets the y coordinate for the text position
    double get_text_y();
    // Gets the spiral angle for the text position
    double get_spiral_angle();
    // Gets the angle in degrees for the text position
    double get_text_angle();
    
    /* 
     * Overloading the ostream<< function: 
     * 
     * Reports in a nicely formatted way the state of a Spiral object. Relies 
     * on users of this function to provide any desired newlines after 
     * outputting the spiral object. 
     */
    friend std::ostream& operator<<(std::ostream& output, Spiral spiral);
};

#endif