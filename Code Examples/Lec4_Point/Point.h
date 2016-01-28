/* Example code for CS3505 lecture 3
 * shows building a simple Point class
 * David Johnson
 */
#include <iostream>
using namespace std;

// The Point class holds 2D points and lets you scale them and output them
class Point {
  double x,y;
public: // accessible methods
  // Constructors
  Point(); // a default constructor.
  Point(int x, int y); // initializer style
  int get_x();
  void set_x(double newX);
  Point operator*(double scaleFactor);

  // Let the overloaded << function use the private class members
  friend ostream& operator<<(ostream& output, Point pt);
}; // end of the Point class definition
