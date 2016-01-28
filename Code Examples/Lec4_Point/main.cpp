/* Example code for CS3505 lecture 3
 * shows building a simple Point class
 * David Johnson
 */
#include "Point.h"
#include <iostream>
using namespace std;

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
