#include "euler.h"
#include <iostream>
#include <cmath>

using namespace euler;

/*
* class PrimeSieve
* Provides operations that involve prime numbers, such as counting divisors or generating primes
*/

PrimeSieve::PrimeSieve(int64_t lim) {
	if (lim < 0)
	{
		std::cout << "Limit was negative. Inverting limit..." << std::endl;
		lim *= (-1);
	}
	
	_limit = lim;
	_sieve_limit = lim/ 2 + 1;
	
	sieve.resize(_sieve_limit, true);
	populate();
}

// Load the sieve with true / false values
void PrimeSieve::populate() {
	// handle 1, first odd number (not a prime)
	sieve[0] = false;
	primes.push_back(2);
	
	for (int64_t i = 1; i < _sieve_limit; i++)	{
		// mark off every number afterwards, starting at i**2 = ((2i + 1)**2 - 1)/2
		if (sieve[i]) {
			for (int64_t j = 2 * i * (i + 1); j < _sieve_limit; j += (2 * i + 1))
				sieve[j] = false;
			primes.push_back(2 * i + 1);
		}
	}
}

// Operator overload, bracket: s[n] returns TRUE if n is prime
bool PrimeSieve::operator[](const int64_t &candidate) {
	// make sure operator is in range 0 <= < lim
	if (candidate < 0 || candidate > _limit)
	{
		std::cerr << "Operator[] out of range. Returning false." << std::endl;
		return false;
	}
	
	// eliminate small and even numbers
	if (candidate == 2)
		return true;
	if (candidate % 2 == 0)
		return false;
	
	// check if number is prime in sieve
	int64_t i = (candidate - 1)/ 2;
	if (i > _sieve_limit) {
		std::cerr << "Pseudoassertion: The index was out of sieve bounds. This should never have happened -- start debugging!" << std::endl;
		return false;
	}
	return sieve.at(i);
}

void PrimeSieve::prime_factorization(const int64_t n, std::map<int, int> &factors_map) {
	// Make sure the map is empty
	if (!factors_map.empty() ) {
		std::cerr << "Please pass an empty map into void prime_factorization (euler.cpp).";
		return;
	}
	// Initialize a copy of number and the divisor counter (to be multiplied)
	int64_t factored_num = n;
	// Find prime factors and the number of times that each one divides into the number
	for (uint64_t i = 0, z = primes.size(); i < z && factored_num != 1; i++)
	{
		int prime_pow = 0;
		while (factored_num % primes[i] == 0) {
			factored_num /= primes[i];
			prime_pow += 1;
		}
		
		// Add the prime factor and its power if it divided
		if (prime_pow != 0) {
			factors_map.insert(std::pair<int, int>(primes[i], prime_pow) );
		}
	}
	
	if (factored_num != 1) {
		std::cout << n << ", " << factored_num << std::endl;
		std::cerr << "Number could not be factored properly (euler.cpp)." << std::endl;
	}
}

// Find the number of divisors in a number using the primes list
unsigned int PrimeSieve::num_divisors(const int64_t n) {
	std::map<int, int> factors;
	unsigned int divisors = 1;
	prime_factorization(n, factors);
	for (std::map<int, int>::iterator it = factors.begin(); it != factors.end(); it++) { 
		divisors *= (it->second + 1);
	}
	return divisors;
}

int PrimeSieve::sum_of_divisors(int n) { 
	// Find prime factorization of number
	std::map<int, int> prime_fact;
	prime_factorization(n, prime_fact);

	// Iterate through each prime factor and use the equation sum[(p^(m+1) - 1) / p - 1]
	int64_t numerator = 1;
	int64_t denominator = 1;
	for (std::map<int, int>::iterator i = prime_fact.begin(); i != prime_fact.end(); i++) {
		int prime_factor = i-> first;
		int power = i-> second;
		
		// Calculate power, avoiding <cmath>, which only accepts float-types
		int64_t exp_result = 1;
		for (int j = 0; j < power + 1; j++)
			exp_result *= prime_factor;

		numerator *= exp_result - 1;
		denominator *= (i->first) - 1;
	}
	
	int sum = numerator / denominator;
	return sum;
}

PrimeSieve::~PrimeSieve() {
	
}

/*
* int gcd(int x, int y)
* Returns the GCD of two numbers using the Euclidean algorithm
*/
int64_t euler::gcd(int64_t x, int64_t y)
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




/*
* int day_for(int date, int month, int year)
* Uses Zeller's congruence (http://en.wikipedia.org/wiki/Zeller's_Congruence)
* to find the day that a year fell upon, with (Saturday = 0)
*/
int euler::day_for(int date, int month, int year) {
	// In Zeller's congruence, Jan/Feb are month "13 and 14" of the previous year
	if (month <= 2) {
		year -= 1;
		month += 12;
	}
	int k = year % 100;
	int j = year / 100;
	int day_of_week = (date + (13 * (month + 1))/5 + k + (k / 4) + (j / 4) + 5 * j) % 7;
	
	return day_of_week;
}

/*
 *  bool is_perf_square(int64_t n)
 *  Returns whether n is a perfect square
 *  Adapted from John D. Cook's post, StackOverflow
 */
bool euler::is_perf_square(int64_t n) {
    unsigned int unit = (n & 0xF);
    if (unit > 9 || (unit != 1 && unit != 4 && unit != 9 && unit != 0))
        return false;

    int64_t root = static_cast<int64_t>(floor(sqrt(n) + 0.5));
    return (root * root == n);
}

/*
* bool is_pentagonal(int x), bool is_hexagonal(int x)
* Returns true if x is a pentagonal or hexagonal number
*/

bool euler::is_pentagonal(int64_t x) {
    if (!is_perf_square(24 * x + 1))
        return false;
    int64_t numerator = static_cast<int64_t>(floor(sqrt(24 * x + 1) + 0.5)) + 1;
    return numerator % 6 == 0;
}

bool euler::is_hexagonal(int64_t x) {
    if (!is_perf_square(8 * x + 1))
        return false;
    int64_t numerator = (static_cast<int64_t>(floor(sqrt(8 * x + 1))) + 1);
    return numerator % 4 == 0;
}