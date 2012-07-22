/*********************************************************
Project Euler 36 (pe36.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)

NOTES
Need two functions: telling if a number is a palindrome in base 10, and if in base 2
For base 2, we can flip the whole thing and right shift until all zeroes go away

Things learned:
BE CAREFUL WITH ORDER OF OPERATIONS IN EQUALITY OF BITWISE OPERATORS
USE UNSIGNED NUMBERS or >> means signed shift, keeping the least significant bit
*********************************************************/

#include <iostream>
#include <stdlib.h>

const int kLimit = 1000000;

bool is_palindrome(const int n);
bool is_palindrome_b2(const unsigned int n);

int main() {
	int sum = 0;
	
	for (int i = 1; i < kLimit; i++) {
		if (is_palindrome(i) && is_palindrome_b2(i))
			sum += i;
	}
	
	std::cout << sum << std::endl;
}

bool is_palindrome(const int n) {
	int n_mutable = n, reversed = 0;
	for (; n_mutable != 0; n_mutable /= 10)
		reversed = (reversed * 10) + n_mutable % 10;
	return (n == reversed);
}

bool is_palindrome_b2(const unsigned int n) {	
	unsigned int reversed = 0;
	unsigned int n_mut = n;
	for (unsigned int i = 0; i < (sizeof(n) * 8) - 1; i++) {
		// Take the first bit of n and make it the last bit of reversed
		if ((n_mut & 1) == 1)
			reversed = (reversed | 0x01);

		// Shift n to the right, and reversed to the left
		n_mut >>= 1;
		reversed <<= 1;
		
	}
	
	// Remove leading zeros at the end of reverse
	while ((reversed & 1) == 0) {		
		reversed >>= 1;
	}
	
	return (reversed == n);
}

