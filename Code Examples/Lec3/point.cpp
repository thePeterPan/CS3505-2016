/* Example code for CS3505 lecture 3
 * shows building a simple Point class
 * David Johnson 
 */

#include <iostream>
using namespace std;

// The Point class holds 2D points and lets you scale them and output them
class Point {

  // Private data members
private: // starts off private by default, but make it obvious
  double x,y;

public: // accessible methods
  // Constructors
  Point() {;} // a default constructor.
  // Point(int _x, int _y) { // one style of constructor
  //   x = _x;
  //   y = _y;
  // }
  Point(int x, int y) : x(x), y(y) { } // initializer style

  // Setter/Getter
  // Get the value of the private x data member
  int get_x() {
    return x;
  }
  // Set the value of the private x data member
  void set_x(double _x) {
    x = _x;
  }
  // Should have y accessors here as well  

  // Operators
  // Overload * operator to scale.
  // Note that it returns a copy of the local res Point  
  Point operator*(double scaleFactor) {
    Point res(x * scaleFactor, y * scaleFactor);
    // Point res;
    // res.x = x * scaleFactor;
    // res.y = y * scaleFactor;
    
    return res;
  };

  // Let the overloaded << function use the private class members
  friend ostream& operator<<(ostream& output, Point pt);
}; // end of the Point class definition
  
// Since the lefthand side is an ostream, we cannot
// add to that class directly. Make function that accepts two args, the
// lhs and rhs of the operation.
ostream& operator<<(ostream& output, Point pt)
{
  output << "(" << pt.x << "," << pt.y << ")";
  return output;
}

// Some test code
int main() {
  Point a;
  Point b(10.0, 20.0);

  double b_x = b.get_x();
  Point c = b * 2.0;

  cout << "b: " << b << endl;
  cout << "c: " << c << endl;
  
  return 0;
}
