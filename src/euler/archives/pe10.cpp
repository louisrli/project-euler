/* The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million. */

using namespace std;
#include <iostream>
#include <cmath>

typedef unsigned long long ull;
const unsigned int limit = 2000000;

bool isPrime(ull);

int main()
{
	ull sum = 2;
	for (unsigned int i = 3; i <= limit; i += 2)
	{
		if (isPrime(i))
			sum += i;
	}
	cout << sum << endl;
}

bool isPrime(ull x)
{
	for (ull i = floor(sqrt(x)), n = floor(x / 3.0); i <= n; i++)
	{
		if (x % i == 0 && i != 1)
			return false;
	}
	cout << "Prime found: " << x << endl;
	return true;
}