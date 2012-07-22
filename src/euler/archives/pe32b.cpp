/*********************************************************
Project Euler 32 (pe32.cpp)
Created by Louis Li on 2012-01-03.

CHANGES
This version attempts to optimize the algorithm for converting a vector into numbers

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

bool next_lex_permutation(vector<int> &permutation);
int convert_vector_to_number(int_iter begin, int_iter end);

const int kMaxDigit = 9;
int main() {
	int sum = 0;
	vector<int> digits_vector(kMaxDigit);
	set<int> cache;
	
	for (int i = 0; i < kMaxDigit; i++) {
		digits_vector[i] = i + 1;
	}
			
	// For each permutation, check for a product identity through combinations
	do {
		// Test both boundaries for c = ab
		int bound_upper = (kMaxDigit % 2 == 0) ? kMaxDigit / 2 : (kMaxDigit / 2) + 1;
		for (int boundary = kMaxDigit / 2; boundary <= bound_upper; boundary++) {
			for (int i = 0; i < boundary - 1; i++) {
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
	while (next_lex_permutation(digits_vector) );

	
	cout << sum << endl;
}

// Uses chars to convert a vector range into a number
int convert_vector_to_number(int_iter begin, int_iter end) {
	int power = 0, num = 0;
	for (int_iter i = end - 1; i >= begin; i--, power++)
		num += round(*i * pow(10.0, power));
	return num;
}

/* Implementing this algorithm, taken from http://en.wikipedia.org/wiki/Permutations#Generation_in_lexicographic_order:
" 1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
2. Find the largest index l such that a[k] < a[l]. Since k + 1 is such an index, l is well defined and satisfies k < l.
3. Swap a[k] with a[l].
4. Reverse the sequence from a[k + 1] up to and including the final element a[n]."" */
bool next_lex_permutation(vector<int> &permutation) {
	unsigned int digits = permutation.size();
	unsigned int k = 0, l = 0;
	
	// Find the indexes k and l
	bool k_found = false;
	for (unsigned int i = 0; i < digits - 1; i++) {
		// Ensure that we're only dealing with single digits for lexicographic order
		if (permutation.at(i) < 0 || 9 < permutation.at(i))
			cerr << "Warning: trying to find the lexicographic permutation with a non-positive digit." << endl;
		
		if (permutation.at(i) < permutation.at(i + 1)) {
			k = i;
			k_found = true;
		}
		
		if (permutation.at(k) < permutation.at(i + 1))
			l = i + 1;
	}

	if (!k_found) return false;
	
	// Swap the values at k and l indices and reverse (k + 1) to th eend
	swap(permutation[k], permutation[l]);
	reverse(permutation.begin() + k + 1, permutation.end() );
	return true;
}
