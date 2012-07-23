/* A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

/* NOTES
a. All multiples of abundant numbers are also abundant numbers
b. Abundant numbers are multiples of 2 or 3 until 5391411025

c. All proper multiples of abundant numbers are sums of two abundant numbers

Considerations -- using a set instead of a vector
*/

using namespace std;
#include <iostream>
#include <set>
#include "euler.h"

const int kLimit = 28123;
int main() {
	// Prepare prime sieve 
	PrimeSieve primes(kLimit);
	
	// Initialize sieves to check if a number is 1. abundant or 2. a sum of two abundant numbers
	vector<bool> is_abundant_num(kLimit + 1, false);
	vector<bool> is_sum(kLimit + 1, false);
	
	// Find all abundant numbers through sieving
	for (unsigned int i = 12; i < kLimit + 1; i++) {
		// Continue loop if this number has already been found as a multiple
		if (is_abundant_num[i] == true)
			continue;
			
		// If i is abundant, mark off i as abun. its multiples as abun./sum
		if (i < (primes.sum_of_divisors(i) - i)) {
			is_abundant_num[i] = true;
			
			for (int j = 2 * i; j < kLimit + 1; j += i) {
				is_abundant_num[j] = true;
				is_sum[j] = true;
			}
		}
	}
	
	// Find the numbers that are sums of two abundant numbers
	for (unsigned int i = 12, n = is_abundant_num.size(); i < n; i++) {
		if (!is_abundant_num[i])
			continue;
		
		for (unsigned int j = i + 1; j < (n - i); j++) {
			if (!is_abundant_num[j])
				continue;
			is_sum[i + j] = true;
		}
	}
	
	// Find the sum of all numbers that can't be expressed as a sum of two abun nubmers
	unsigned long long solution = 0;
	for (unsigned int i = 0, n = is_sum.size(); i < n; i++) {
		if (!is_sum[i]) {
			cout << i << endl;
			solution += i;
		}
	}
	
	cout << solution << endl;
}
