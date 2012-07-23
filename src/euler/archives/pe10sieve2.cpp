/* The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million. */

// Improved time by 0.10 seconds by accounting doing j += i * 2 and doing even numbers first

using namespace std;
#include <iostream>
#include <cmath>
#include <vector>
#include "euler.h"

typedef unsigned long long ull;
const unsigned int LIMIT = 2000000;
const unsigned int MARKING_CAP = ceil(sqrt(LIMIT));

int main()
{
	ull sum = 2;
	
	// initialize a Sieve of Eratosthenes for size `limit`, where true indicates primality
	PrimeSieve sieve(LIMIT);
	for (ull i = 3; i < LIMIT; i += 2)
	{
		if (sieve[i])
			sum += i;
	}
	cout << sum << "\n";
}