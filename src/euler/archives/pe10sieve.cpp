/* The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million. */

using namespace std;
#include <iostream>
#include <cmath>
#include <vector>

typedef unsigned long long ull;
const unsigned int LIMIT = 2000000;
const unsigned int MARKING_CAP = ceil(sqrt(LIMIT));

int main()
{
	ull sum = 0;
	
	// initialize a Sieve of Eratosthenes for size `limit`, where true indicates primality
	vector<bool> sieve (LIMIT + 1, true);
	sieve[0] = false;
	sieve[1] = false;
	
	for (ull i = 2; i <= LIMIT; i++)
	{
		if (sieve[i])
		{
			sum += i; // remove this line of code when reusing (included to prevent relooping)
			if (i <= MARKING_CAP)
			{
				for (ull j = i * i; j <= LIMIT; j += i)
					sieve[j] = false;
			}
		}
	}
	
	cout << sum << endl;
}