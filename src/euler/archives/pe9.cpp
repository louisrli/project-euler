/* A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a2 + b2 = c2

For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

/* NOTES
* 1. a + b + c = 1000 and a < b < c
* 2. Approx: a { 1, 332}, b { 2, 499 }; c { 334, 997 }
*/

using namespace std;
#include <iostream>
#include <cmath>

int main()
{
	for (int a = 1; a <= 333; a++)
	{
		for (int b = a + 1; b <= 499; b++)
		{
			int c = 1000 - b - a;
			if (334 <= c && c <= 997 && (a * a + b * b == c * c))
			{
				cout << a * b * c << endl;
			}
		}
	}
}