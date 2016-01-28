/* Example code for CS3505 lecture 3
 * shows building a simple Point class
 * David Johnson
 */
#include "Point.h"
#include <iostream>
using namespace std;

Point::Point() {;}

Point::Point(int x, int y) : x(x), y(y) { } // initializer style

  // Setter/Getter
  // Get the value of the private x data member
int Point::get_x() {
    return x;
  }

  // Set the value of the private x data member
void Point::set_x(double newX) {
    x = newX;
  }
  // Should have y accessors here as well

  // Operators
  // Overload * operator to scale.
  // Note that it returns a copy of the local res Point
Point Point::operator*(double scaleFactor) {
    Point res(x * scaleFactor, y * scaleFactor);
    return res;
  };


// Since the lefthand side is an ostream, we cannot
// add to that class directly. Make function that accepts two args, the
// lhs and rhs of the operation.
ostream& operator<<(ostream& output, Point pt)
{
  output << "(" << pt.x << "," << pt.y << ")";
  return output;
}

