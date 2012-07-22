/*********************************************************
Project Euler 43 (pe43.cpp)
Created by Louis Li on 2012-01-10.

PROBLEM
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

    d2d3d4=406 is divisible by 2
    d3d4d5=063 is divisible by 3
    d4d5d6=635 is divisible by 5
    d5d6d7=357 is divisible by 7
    d6d7d8=572 is divisible by 11
    d7d8d9=728 is divisible by 13
    d8d9d10=289 is divisible by 17

Find the sum of all 0 to 9 pandigital numbers with this property.

NOTES
The goal is to check the substrings without converting them back into numbers (expensive), so using divisibility rules
*********************************************************/

#include <iostream>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

const int kDigits = 10;
const int kBlock = 3;

template<class iter>
bool is_interesting (iter a, iter b);
template<class iter>
uint64_t range_to_num(iter a, iter b);

int main() {
    uint64_t sum = 0;
    
	// Initialize the number vector
    std::vector<int> pandigital(kDigits, 0);
    for (int i = 0; i < kDigits; i++)
        pandigital[i] = kDigits - i - 1;
        
    // Check permutations and skip over relevant ones
    do {
        if (is_interesting(pandigital.begin(), pandigital.end()))
            sum += range_to_num(pandigital.begin(), pandigital.end());
    } while (std::prev_permutation(pandigital.begin(), pandigital.end()) &&
             pandigital[0] != 0);

    std::cout << sum << std::endl;
    return 0;
}

// Takes an iterator as input and checks if it satisfies the problem-specific conditions
template <class iter>
bool is_interesting(iter a, iter b) {
    int primes[] = { 2, 3, 5, 7, 11, 13, 17 };
    for (int i = 1; i <= kDigits - kBlock; i++) {
        int substring = range_to_num(a + i, a + i + kBlock);
        if (substring % primes[i - 1] != 0)
            return false;
    }
    return true;
}

// Concatenates a range (e.g. {1, 2, 3} => 123) to a number
// Assumes each index holds a single digit
template<class iter>
uint64_t range_to_num(iter a, iter b) {
    uint64_t num = 0;
	for (iter i = a; i != b; i++) {
		num += *i * round(pow(10, distance(i, b - 1)));

        // Check that it's a digit
        if (*i < 0 || *i > 10) {
            std::cerr << "Trying to convert a range to a number with nondigits" << std::endl;
            throw 0;
        }
	}
	return num;
}