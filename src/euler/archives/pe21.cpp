/* Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000. */

/* NOTES:
a. Amicable pair members are both even or both odd (not proven for an infinitely large range)
b. Sum of divisors can be found using a geometric series with the prime factorization
*/

using namespace std;
#include <iostream>
#include <vector>
#include <map>
#include "euler.h"
#include <cmath>

typedef map<int, int> intmap;
const int kLimit = 10000;

int sum_of_divisors(int n, PrimeSieve &sieve);

int main() {
	PrimeSieve sieve(100000);
	intmap cached_values;
	int solution = 0;
	
	// Calculate the sum of divisors, s(d) for each number and cache value
	for (int pair_a = 2; pair_a < kLimit; pair_a++) {
		
		// For a pair (a, b), find b either through the cache or through calculation
		bool is_a_cached = cached_values.find(pair_a) != cached_values.end();
		int pair_b = is_a_cached ? cached_values[pair_a] : sum_of_divisors(pair_a, sieve) - pair_a;
		cached_values[pair_a] = pair_b;
		
		// Return immediately if a = b
		if (pair_a == pair_b)
			continue;
			
		// Find d(b) to check if a == d(b) and cache the value of b
		bool is_b_cached = cached_values.find(pair_b) != cached_values.end();
		int d_b = is_b_cached ? cached_values[pair_b] : sum_of_divisors(pair_b, sieve) - pair_b;
		cached_values[pair_b] = d_b;
		
		if (d_b == pair_a) {
			cout << "Amicable pair found: " << pair_b << ", " << pair_a << endl;
			solution += (pair_a);
		}
	}
	
	cout << solution << endl;
}

int sum_of_divisors(int n, PrimeSieve &sieve) { 
	// Find prime factorization of number
	intmap prime_fact;
	prime_factorization(n, prime_fact, sieve);

	// Iterate through each prime factor and use the equation sum[(p^(m+1) - 1) / p - 1]
	long long numerator = 1;
	long long denominator = 1;
	for (intmap::iterator i = prime_fact.begin(); i != prime_fact.end(); i++) {
		int prime_factor = i-> first;
		int power = i-> second;
		
		// Calculate power, avoiding <cmath>, which only accepts float-types
		long long exp_result = 1;
		for (int j = 0; j < power + 1; j++)
			exp_result *= prime_factor;

		numerator *= exp_result - 1;
		denominator *= (i->first) - 1;
	}
	
	int sum = numerator / denominator;
	return sum;
}