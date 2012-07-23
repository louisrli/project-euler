/* Starting in the top left corner of a 2×2 grid, there are 6 routes (without backtracking) to the bottom right corner.

How many routes are there through a 20×20 grid?
*/

/* NOTES
* If A represents going right, and B represents going down, and L is the length:
* There are L + L steps; and L steps of A and L steps of B. ("AAABBAABBB...etc.")
* Therefore, we're looking for the number of possible permutations fitting these constraints
* => (L + L)! / (L!)(L!) = (2L)! / (L!)(L!) = Product([2L...L+1]) / L!
* Because the numbers get too big, this is a rough implementation of large number factorials that can still overload
*/

const int length = 20;

using namespace std;
#include <iostream>	


int main() {
	unsigned long long solution = 1;
	
	for (int j = length * 2; j > length; j--) {
		// handle odd j (39, 37, 35, 33)
		if (j & 1) {
			solution *= j;
		}
		// handle even j (40, 38...divided by (20, 19... 11))
		else {
			solution *= 2;
		}

	}
	
	// divide out (n/2)!
	for (int i = length / 2; i > 0; i--) {
		solution /= i;
	}
	
	cout << solution << endl;
}

