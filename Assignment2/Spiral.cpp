/*
 * Peter Pan
 * u0680482
 * CS3505
 * Assignment 2 
 * 
 * Spiral class
 * The Spiral class should not have any haru functionality, although it should 
 * share the haru sense of coordinate systems and scale (in other words, you do 
 * not need to figure out the units of both and make them consistent).
 */

#include "Spiral.h"     // Header file
#include <iostream>     // ostream

using namespace std;

// Constructor using member initialization
Spiral::Spiral(double centerX, double centerY, double angle, double startingRadius)
            : centerX(centerX), centerY(centerX), angle(angle), startingRadius(startingRadius) {}

// Destructor:
Spiral::~Spiral() { }

/**
 * Advances the spiral character to the next position. 
 * Postfix increment operator. 
 * @param 
 * @return 
 */
Spiral Spiral::operator ++(int) {
    
    return *this;
}

/**
 * Advances the spiral character to the next position.
 * Prefix increment operator. 
 * @return 
 */
Spiral& Spiral::operator ++() {
    
    return *this;
}

/**
 * Public accessor method for the x coordinate
 * @return 
 */
double Spiral::get_text_x() {
    return centerX;
}

/**
 * Public accessor method for the y coordinate
 * @return 
 */
double Spiral::get_text_y() {
    return centerY;
}

/**
 * Public accessor method for the current angle
 * @return 
 */
double Spiral::get_spiral_angle() {
    return angle;
}

/**
 * Public accessor method for the current text angle
 * @return 
 */
double Spiral::get_text_angle() {
    
}

/**
 * 
 * @param output
 * @param spiral
 * @return 
 */
ostream& operator <<(ostream& output, Spiral spiral) {
    
    return output;
}