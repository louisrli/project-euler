/* A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a2 + b2 = c2

For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

/* NOTES
* 1. s = 2md(m + n) = 2mk * d where k = (m + n)
* 2. k = m + n; 0 < n < m => m < m + n < 2m => m < k < 2m -- Limiting the scope of n
* 3. d = s/(2mk) => s/2 must be divisible by both m and (m + n) = k, where gcd(m, k) = 1 (because d multiples a primitive triplet)
*/

using namespace std;
#include <iostream>
#include <cmath>

int gcd(int, int);

const int s = 1000;
const int u = s / 2;

int main()
{
	for (int m = 2, cap = ceil(sqrt(u)); m < cap; m++)
	{
		// Check that s/2 is divisible by m
		if (u % m == 0)
		{
			int multipleK = u / m;
			// Find divisor k for s/(2m)
			for (int k = m; k < 2 * m && k < multipleK; k++)
			{
				if (multipleK % k == 0 && gcd(k, m) == 1)
				{
					// Found a d -- now use parameterization to find a, b, c
					int d = multipleK / k;
					int a = (m * m - (k - m) * (k - m)) * d;
					int b = (2 * m * (k - m)) * d;
					int c = (m * m + (k - m) * (k - m)) * d;
					int answer = a * b * c;
					cout << "Product: " << answer << endl;
					return 1;
				}
			}
		}
	}
}

int gcd(int x, int y)
{
	// swap numbers if y > x
	if (y > x)
		return gcd(y, x);
	// end case for Euclidean algorithm
	if (y == 0)
		return x;
	else
		return gcd(y, x % y);
		
}