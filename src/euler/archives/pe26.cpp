/* A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

    1/2	= 	0.5
    1/3	= 	0.(3)
    1/4	= 	0.25
    1/5	= 	0.2
    1/6	= 	0.1(6)
    1/7	= 	0.(142857)
    1/8	= 	0.125
    1/9	= 	0.(1)
    1/10	= 	0.1

Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part. */

/* NOTES
1. For any number n coprime to ten, period = multiplicative order of 10 mod n
2. Multiples of primes will have the same period 
Therefore, only need to test numbers coprime to ten / primes */

using namespace std;
#include <iostream>
#include "euler.h"
#include <vector>

int modular_exp(int base, int exp, int mod);
int mult_order(int base, int mod);

const int kLimit = 1000;

int main() {
	int current_max_period = 0;
	int d = 0;
	PrimeSieve s(kLimit);
	vector<long long> primes = s.getPrimes();
	
	// Only test values coprime to ten & primes for multiplicative order
	for (int i = 3; i < primes.size(); i++) {
		// Store the largest period number and its corresponding value d for 1/d
		int period = mult_order(10, primes[i]);
		if (period > current_max_period) {
			current_max_period = period;
			d = primes[i];
		}
	}
	
	cout << d << endl;
	cout << current_max_period << endl;
}
int mult_order(int base, int mod) { 
	// Check if gcd(base, mod) is 1
	
	// Test all exponents for modular exponentiation
	int exp = 1;
	while (modular_exp(base, exp, mod) != 1) {
		exp++;
	}
	return exp;
}

// Adapted from Wikipedia -- modular exponentiation
int modular_exp(int base, int exp, int mod) { 
	if (mod == 0) {
		cerr << "error: Attempted modulus with zero." << endl;
		throw;
	}
	
	int result = 1;
	while (exp > 0) {
		if (exp & 1 == 1) {
			result = (result * base) % mod;
		}
		exp = exp >> 1;
		base = (base * base) % mod;
	}
	
	return result;
}