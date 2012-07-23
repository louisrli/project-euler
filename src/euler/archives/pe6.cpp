/* The sum of the squares of the first ten natural numbers is,
12 + 22 + ... + 102 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)2 = 552 = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum. */

/* NOTES
* 1. The nth square pyramidal number is given by (1/6)(n)(n + 1)(2n + 1)
* 2. The sum of the first n consecutive integers is given by (1 + n)(n / 2)
*/

using namespace std;
#include <iostream>
#include <cmath>

int main()
{
	const int n = 100;
	// Let x be the sum of the consecutive numbers. Let y be the square pyramidal number for n = 100.
	int x = round((1 + n) * (n / 2.0));
	long long y = round((1.0 / 6) * n * (n + 1) * (2 * n + 1));
	
	long long answer = x * x - y;
	cout << answer << endl;
}