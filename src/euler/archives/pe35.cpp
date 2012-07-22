/*********************************************************
Project Euler 35 (pe35.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

NOTES
	Search space constraints:
	1. No even digits in number: {100, 300, 500...} + {10, 30, 50 ... } + {1, 3, 5, 7}
	2. Does not contain 5
*********************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "euler.h"

const int kLimit = 1000000;
const int kDigitsLimit = 6;

bool has_even_digits(int n);
bool is_circular_prime(const int n, euler::PrimeSieve &prime_sieve);

int main() {
	// Initialize relevant variables and count 2 as a prime
	int circular_primes = 1;
	euler::PrimeSieve sieve(kLimit);
	
	// Check odd numbers for circular primality
	for (int i = 3; i < kLimit; i += 2)
			if(is_circular_prime(i, sieve))	circular_primes++;
	
	std::cout << circular_primes << std::endl;
}

// Check if a number is a circular prime by comparing every rotation with a prime sieve
bool is_circular_prime(const int n, euler::PrimeSieve &prime_sieve) {
	if (has_even_digits(n)) return false;
	
	int n_shift = n, n_digits = 0;
	for (int x = n; x != 0; x /= 10) n_digits++;
	
	for (int i = 0; i < n_digits; i++) {
		// Check if current rotation is prime and then rotate it
		if (!prime_sieve[n_shift]) return false;
		n_shift = (n_shift / 10) + round(pow(10, n_digits - 1)) * (n_shift % 10);
	}
	return true;
}


bool has_even_digits(int n) {
	for (; n != 0; n /= 10) {
		if (n % 2 == 0) return true;
	}
	return false;
}