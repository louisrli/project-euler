/* Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

/* It seems that all of these can be based off the square value of the width:
where step = (width - 1)/2, or (n - 1)/2
sum += (width * width) // NE
sum += (width * width) - (step * 2); // NW
sum += (width * width) - (step * 6); // SE
sum += (width * width) - (step * 4); // SW
=> sum += (4)(width * width) - 12 * (width - 1) / 2 -> 4 * width * width - 6 * width - 6
*/ 
using namespace std;
#include <iostream>

const int kSpiralWidth = 1001;

int main() {	
	// Compute sum along each diagonal (excl. 1), given the width of the spiral
	long long sum = 1;
	for (int width = 3; width <= kSpiralWidth; width += 2)
		sum += 4 * width * width - 6 * width - 6;
		
	cout << sum << endl;
}