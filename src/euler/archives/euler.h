#ifndef EULER_H
#define EULER_H

#include <vector>
#include <map>
#include <stdint.h>

namespace euler {
	// class PrimeSieve: a class for operations relating to prime numbers
	class PrimeSieve  {
	public:
		explicit PrimeSieve(int64_t lim = 1000000);
		~PrimeSieve();
		int64_t limit() { return _limit; };
		bool operator[](const int64_t &candidate);
		const std::vector<int64_t>& getPrimes() const { return primes; };
		
		void prime_factorization(const int64_t n, std::map<int, int> &factors_map);
		unsigned int num_divisors(const int64_t n);
		int sum_of_divisors(int n); 
		
	private:
		void populate();
		std::vector<bool> sieve;
		int64_t _limit;
		int64_t _sieve_limit;
		std::vector<int64_t> primes;
	};
	
	int64_t gcd(int64_t x, int64_t y);

/*
* int day_for(int date, int month, int year)
* Uses Zeller's congruence (http://en.wikipedia.org/wiki/Zeller's_Congruence)
* to find the day that a year fell upon, with (Saturday = 0)
*/
int day_for(int date, int month, int year);


/*
 *  bool is_perf_square(int64_t n)
 *  Returns whether n is a perfect square
 *  Adapted from John D. Cook's post, StackOverflow
 */
bool is_perf_square(int64_t n);

/*
* bool is_pentagonal(int64_t x), bool is_hexagonal(int64_t x)
* Returns true if x is a pentagonal or hexagonal number
*/
bool is_pentagonal(int64_t x);
bool is_hexagonal(int64_t x);

}
#endif
