#include <iostream> // needed for output
using namespace std; // cout and endl are in the std namespace

bool isEven(int); // forward declaration of isEven

// Definition of isOdd
bool isOdd( int number ) {
    if (number == 0)
	return false;
    else
	return isEven( number - 1 );
}

// Definition of isEven
bool isEven( int number )
{
    if (number == 0)
	return true;
    else
	return isOdd( number - 1 );
}

/*  The main function.
 *  It computes whether numbers from 1 to 10 are even or odd
 *  with a messy double-recursive computation.
 */
int main() {
    for (int number = 1; number < 10; ++number) {
	if (isOdd(number)) 
	    cout << number << " is odd" << endl;
	else
	    cout << number << " is even" << endl;
    }
}


