/* By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
*/

using namespace std;
#include <iostream>
#include <cmath>

typedef unsigned long long ull;

bool isPrime(ull);

int main()
{
	const int targetPrime = 10001;
	int prime = 1;
	ull candidate = 3;
	ull largestPrime = 0;
	while (prime < targetPrime)
	{
		if (isPrime(candidate))
		{
			largestPrime = candidate;
			prime++;
		}
		candidate += 2;
	}
	
	cout << largestPrime << endl;
}

bool isPrime(ull x)
{
	for (ull i = floor(sqrt(x)), n = floor(x / 3.0); i <= n; i++)
	{
		if (x % i == 0 && i != 1)
			return false;
	}
	return true;
}