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
#include <iostream>

using namespace std;

// Constructor using member initialization
Spiral::Spiral(double centerX, double centerY, double angle, double startingRadius) :
		centerX(centerX), centerY(centerX), angle(angle), startingRadius(startingRadius) {}

// Destructor:
Sprial::~Spiral() { }