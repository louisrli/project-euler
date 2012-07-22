/*********************************************************
Project Euler 37 (pe37.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

NOTES

*********************************************************/

#include <iostream>
#include <vector>
#include <numeric>
#include "euler.h"
#include <cmath>

const int kLimit = 3000000;
bool is_trunc_prime(const int64_t n, euler::PrimeSieve &sieve);

int main() {
	std::vector<int64_t> trunc_primes;
	
	// Generate a list of primes and check if each prime is truncatable
	euler::PrimeSieve sieve(kLimit);
	std::vector<int64_t> primes = sieve.getPrimes();
	
	for (int i = 5; trunc_primes.size() != 11 && i < primes.size(); i++)
		if (is_trunc_prime(primes[i], sieve)) trunc_primes.push_back(primes[i]);

	int64_t solution = std::accumulate(trunc_primes.begin(), trunc_primes.end(), 0);
	std::cout << solution << std::endl;
	
}

bool is_trunc_prime(const int64_t n, euler::PrimeSieve &sieve) {
	// Find number of digits in the number
	int digits = 0;
	for (int64_t n_mut = n; n_mut != 0; n_mut /= 10) digits++;

	int left = n, right = n;
	do {
		// Check if either truncation is prime, includes n
		if (!sieve[right] || !sieve[left])
			return false;

		// Truncate the right and left digits
		left %= (int) round(pow(10, --digits));
		right /= 10;
	}
	while (right != 0 && left != 0);
	
	// All truncations were prime, so this is a truncatable prime
	return true;
}