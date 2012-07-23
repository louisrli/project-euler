/*********************************************************
Project Euler 33 (pe33.cpp)
Created by Louis Li on 2012-01-03.

PROBLEM
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

NOTES
a. Numerator is always less than denominator
b. Given a numerator of digits form AB, we have to test denominators Ax, xA, Bx, and xB > AB
xB -- AB += 10
Bx -- If B < A, skip since (AB / BA) > 1. If B = A, skip since it'll be tested in another case. If B > A, test (AB / BC) where C[0, 9]
Ax -- Test numbers in range x[B, 9]
xA -- Test numbers (AB/xA) x[A, 9] (if A < B)

REUSE
This code is not a generalized case; it only works with two digit numbers as the problem specifies.

TIMELINE NOTES
Just included a major refactoring, using the `euler` namespace for "euler.h"
*********************************************************/

using namespace std;
#include <iostream>
#include <numeric>
#include "euler.h"
#include <stdint.h>

bool is_curious_fraction(int numerator, int denominator);

const int kStart = 10;
const int kEnd = 100;

int main() {
	vector<int> numerators;
	vector<int> denominators;
	
	for (int i = kStart; i < kEnd - 1; i++) {
		for(int j = i + 1; j < kEnd; j += 1)
		{
			// Check for digits that "cancel out" (premature optimization?)
			if (j % 10 != i % 10 && 
				j % 10 != i / 10 && 
				j / 10 != i % 10 && 
				j / 10 != i / 10)
					continue;
			
			// Record fraction if curious
			if (is_curious_fraction(i, j)) {
				numerators.push_back(i);
				denominators.push_back(j);
			}
		}
	}	
	
	int64_t numerator_prod = accumulate(numerators.begin(), numerators.end(), 1, multiplies<int64_t>());
	int64_t denominator_prod = accumulate(denominators.begin(), denominators.end(), 1, multiplies<int64_t>());
	int64_t solution = denominator_prod / euler::gcd(numerator_prod, denominator_prod);
	
	cout << solution << endl;
}

bool is_curious_fraction(int numerator, int denominator) {
	// Return false for trivial cases
	if (numerator % 10 == 0 && denominator % 10 == 0) return false;
	
	// Decompose the numerator and denominator into individual digits
	int digits_numer[2] = { numerator / 10, numerator % 10 };
	int digits_denom[2] = { denominator / 10, denominator % 10 };
	
	// Reduce the numerator
	int reduc_factor = euler::gcd(numerator, denominator);
	numerator /= reduc_factor;
	denominator /= reduc_factor;
	
	// Check if any of the digits are equal -- if they are, "cancel them out" and compare to normal reduction
	for(unsigned int i = 0; i <= 1; i++)
		for(unsigned int j = 0; j <= 1; j++)
			if (digits_numer[i] == digits_denom[j] &&
				digits_numer[!i] / euler::gcd(digits_numer[!i], digits_denom[!j]) == numerator &&
				digits_denom[!j] / euler::gcd(digits_numer[!i], digits_denom[!j]) == denominator)
					return true;
	return false;
}
