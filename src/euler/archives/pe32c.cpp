/*********************************************************
Project Euler 32 (pe32.cpp)
Created by Louis Li on 2012-01-03.

CHANGES
Optimized for loop to end at (boundary / 2), since  ab * cde = cde * ab (repeated permutations)
PROBLEM
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

NOTES
Let d(n) be the number of digits in a number.
if c = ab, d(c) = (d(a) + d(b) - 1) || (d(a) + d(b))
*********************************************************/

using namespace std;
#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>
#include <cmath>

typedef vector<int>::iterator int_iter;

int convert_vector_to_number(int_iter begin, int_iter end);

const int kMaxDigit = 9;
int main() {
	int sum = 0;
	vector<int> digits_vector(kMaxDigit);
	set<int> cache;
	
	for (int i = 0; i < kMaxDigit; i++)
		digits_vector[i] = i + 1;
			
	// For each permutation, check for a product identity through combinations
	do {
		// Test both boundaries for c = ab
		int bound_upper = (kMaxDigit % 2 == 0) ? kMaxDigit / 2 : (kMaxDigit / 2) + 1;
		for (int boundary = kMaxDigit / 2; boundary <= bound_upper; boundary++) {
			for (int i = 0; i < boundary / 2; i++) {
				int_iter digits_begin = digits_vector.begin();
				int a = convert_vector_to_number(digits_begin, digits_begin + i + 1);
				int b = convert_vector_to_number(digits_begin + i + 1, digits_begin + boundary);
				int c = convert_vector_to_number(digits_begin + boundary, digits_vector.end() );
				
				if (a == 1 || b == 1) continue;
				
				// If the product identity is valid, cache 'c' and compute
				if (a * b == c && cache.find(c) == cache.end() ) {
					sum += c;
					cache.insert(c);
				}
			}
		}
	}
	while (next_permutation(digits_vector.begin(), digits_vector.end() ) );

	
	cout << sum << endl;
}

// Converts the members of a vector int to a number
int convert_vector_to_number(int_iter begin, int_iter end) {
	int power = 0, num = 0;
	for (int_iter i = end - 1; i >= begin; i--, power++)
		num += round(*i * pow(10.0, power));
	return num;
}