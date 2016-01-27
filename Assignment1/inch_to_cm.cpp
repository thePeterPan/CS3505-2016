/*
* File:   inch_to_cm.cpp
* Author: Peter Pan
* Uid:    u0680482
* Class:  CS 3505
*
* Created on January 21, 2016
*/

#include <cstdlib>
#include <iostream>     // std::cout
#include <iomanip>      // std::setprecision
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <cstdlib>      // std::strtod

using namespace std;

/*
* Returns a double which is the input parameter converted from
* inches to centimeters.
* @param inches
* @return
*/
double convertInchToCm(double inches) {
	return inches * 2.54;
}

/*
* Outputs the parameter to standard out to two decimal places
* of precision (there should always be two digits after the
* decimal point) followed by a newline.
*
* @param centimeters
*/
void niceOutput(double centimeters) {
	std::cout << std::setprecision(2) << std::fixed << centimeters << std::endl;
}

/*
*
*/
int main(int argc, char** argv) {

	// variable for cin
	std::string line;

	// loop through the 
	while (std::getline(std::cin, line))
	{
		std::stringstream ss(line);
		std::string inches;
		char* end;
		// if the line has multiple values, iterate through each
		while (std::getline(ss, inches, ' ')) {
			// convert individual string values to double type
			double inchesDouble = std::strtod(inches.c_str(), &end);
			// convert inches to centimeters and print them out
			niceOutput(convertInchToCm(inchesDouble));
		}
	}

	return 0;
}

//int main(int argc, char** argv) {
//    double tempvar = 0.3;
//    std::cout << std::setprecision(30) << std::fixed << tempvar << endl;
//}