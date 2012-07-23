/*********************************************************
Project Euler 34 (pe34.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.

NOTES
	Possible optimizations:
	Let m(d) be the largest digit in a number. Only check numbers greater than m(d)!, since anything less than m(d)! that contains m(d) isn't a possible sum
Given "all numbers," there has to be an upper limit
	Base it on 9! and a "999.. number", where a sum is only possible when 9! * (digits) >= 9{d} --> 
	: 9! * 9 < 9{9}
	: 9! * 7 = 2540160 < 9999999
	: 9! * 6 = 2177280 > 999999
Therefore, the upper bound is "between" 6 and 7, and we pick the ceiling: 7.
*********************************************************/

using namespace std;
#include <iostream>
#include <boost/math/special_functions/factorials.hpp>

const int kFactorialMax = 9;

int main() {
	unsigned int factorials[10];
	for(int i = 0; i < kFactorialMax + 1; i++)
		factorials[i] = static_cast<unsigned int>(boost::math::factorial<double>(i));
	
	uint64_t sum = 0;
	const unsigned int kSearchMax = factorials[9] * 7;

	// Compute the sum of factorial digits in the search space
	for(unsigned int i = 11; i < kSearchMax; i++)
	{
		uint64_t sum_of_digits = 0;
		for (unsigned int i_mutable = i; i_mutable != 0; i_mutable/= 10)
			sum_of_digits += factorials[i_mutable % 10];
		if (sum_of_digits == i)
			sum += i;
	}
	
	cout << sum << endl;	
}