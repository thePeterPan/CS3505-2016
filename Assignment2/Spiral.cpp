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
#include <cmath>        // M_PI

// Sometimes this is needed in older versions/Visual C++
#define _USE_MATH_DEFINES

// Constructor using member initialization
Spiral::Spiral(double centerX, double centerY, double angle, double startingRadius)
            : centerX(centerX), centerY(centerY)
{
    // Clamp the minimum starting radius.
    currentRadius = (startingRadius < 50) ? 50 : startingRadius;
    
    // Add 90 degrees because: "starting angle clockwise from vertical".
    currentSpiralAngle = angle + 90;
            
    calculateSpiral();
}

// Destructor:
Spiral::~Spiral() { }

/**
 * Advances the spiral character to the next position. 
 * Postfix increment operator. 
 * @param 
 * @return 
 */
Spiral Spiral::operator ++(int) {
    incrementSpiralPosition();
    return *this;
}

/**
 * Advances the spiral character to the next position.
 * Prefix increment operator. 
 * @return 
 */
Spiral& Spiral::operator ++() {
    incrementSpiralPosition();
    return *this;
}

/**
 * Helper method for moving the spiral to the next position. 
 * Moves the spiral object to the next position, used in the increment operator.
 */
void Spiral::incrementSpiralPosition() {
    // Decrement the currentSpiralAngle to move the character around in a circle
    currentSpiralAngle -= spacingGrowthRate;
    // Decrease the spacing growth rate to accommodate bigger radii
    spacingGrowthRate -= 0.05;
    
    // Slowly increase the radius making it a spiral
    currentRadius += radiusGrowthRate;   
}

/**
 * Helper method for moving the spiral to the next position.
 * Performs calculations for the current position of the spiral
 */
void Spiral::calculateSpiral() {
    // Calculate the angle of the letter in radians
    currentTextAngle = (currentSpiralAngle - 90) / 180 * M_PI;
    // Calculate the position angle of the letter on the circle in radians
    double currentPosAroundCircle = currentSpiralAngle / 180 * M_PI;

    // Calculate the location of the letter on the document
    currentX = centerX + cos(currentPosAroundCircle) * currentRadius;
    currentY = centerY + sin(currentPosAroundCircle) * currentRadius;
}

/**
 * Public accessor method for the x coordinate
 * @return 
 */
double Spiral::get_text_x() {
    return currentX;
}

/**
 * Public accessor method for the y coordinate
 * @return 
 */
double Spiral::get_text_y() {
    return currentY;
}

/**
 * Public accessor method for the current angle position around the circle
 * @return 
 */
double Spiral::get_spiral_angle() {
    return currentSpiralAngle;
}

/**
 * Public accessor method for the current angle of the character
 * @return 
 */
double Spiral::get_text_angle() {
    return currentTextAngle;
}

/**
 * 
 * @param output
 * @param spiral
 * @return 
 */
std::ostream& operator <<(std::ostream& output, Spiral spiral) {
    output << "Center Position: (" << spiral.centerX << ", " << spiral.centerY << "), " <<
            "Current Char Position: (" << spiral.currentX << ", " << spiral.currentY << "), " <<
            "Radius: " << spiral.currentRadius << ", " << 
            "Spiral angle: " << spiral.currentSpiralAngle << ", " << 
            "Text angle: " << spiral.currentTextAngle;
    return output;
}