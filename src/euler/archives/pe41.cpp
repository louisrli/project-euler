/*********************************************************
Project Euler 41 (pe41.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?

NOTES
Start from n = 9 down to n = 1
Number can't be even
--
sum(1..9) = 45, which means all pandigital 1 to 9 follow the 3 divisibility rule
sum(1..8) = 36 -- none
sum(1..7) = 28 -- candidate
6 : 21 (none); 5 : 16 (candidate); 4: 12 (none); 3 : 6 (none); 2 : 3 (candidate)
*********************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include "euler.h"
#include <algorithm>

const uint64_t kLimit = 10000000;
const int kDigits = 7;

template<class iter>
int range_to_num(iter a, iter b);

int main() {
	euler::PrimeSieve sieve(kLimit);
	
	// Initialize vector of number in highest lexicographic order
	std::vector<int> number(kDigits);
	for (int i = 0; i < kDigits; i++) {
	  number[i] = kDigits - i;
	}
	
	// Return the first prime number
	do {		
	  if (sieve[range_to_num<std::vector<int>::iterator>(number.begin(), number.end() )]) {
	    std::cout << range_to_num(number.begin(), number.end() ) << std::endl;
	    return 0;
	  }
	}
	while (std::prev_permutation(number.begin(), number.end()));
	std::cout << "Number not found." << std::endl;
}

// Concatenates a range (e.g. {1, 2, 3} => 123) to a number, assuming each one is a single digit
template<class iter>
int range_to_num(iter a, iter b) {
	if (*a < 0 || *a > 10 || *b < 0 || * b > 10) {
		std::cerr << "Trying to convert a range to a number without digits." << std::endl;
		throw;
	}
	
	int num = 0;
	for (iter i = a; i != b; i++) {
		num += *i * round(pow(10, distance(i, b - 1)));
	}
	return num;
}
