/*********************************************************
Project Euler 34 (pe34adapted.cpp)
Created by Louis Li on 2012-01-05.

Solution adapted from: http://www.mathblog.dk/project-euler-32-pandigital-products/
This solution takes a different approach, narrowing the search space by multiplying numbers. In retrospect, it's hard to
say whether I would have gone for a similar approach, but it's much, much faster.
The pandigital algorithm was taken from: 
http://stackoverflow.com/questions/2484892/fastest-algorithm-to-check-if-a-number-is-pandigital
*********************************************************/

using namespace std;
#include <iostream>
#include <set>
#include <cmath>

int concatenate_numbers(long long a, long long b);
bool is_pandigital(long long n);

int main() {
	int sum = 0;
	set<int> cache;
	
	for (int i = 2; i < 100; i++) {
		for (int j = 123; j < 10000 / i + 1; j++) {
			long long product = i * j;
			long long pandigital_cand = concatenate_numbers(concatenate_numbers(i, j), product);
			
			if (is_pandigital(pandigital_cand) && pandigital_cand > pow(10.0, 8) && cache.find(product) == cache.end()) {
				sum += product;
				cache.insert(product);
			}
		}
	}
	
	cout << sum << endl;
}

int concatenate_numbers(long long a, long long b) {
	long long c = b;
    while (c > 0) {
        a *= 10;
        c /= 10;
    }
    return a + b;
}

bool is_pandigital(long long n)
{
    int digits = 0, count = 0, tmp;

    for (; n > 0; n /= 10, ++count)
    {
        if ((tmp = digits) == (digits = digits | (1 << (n - ((n / 10) * 10) - 1))))
            return false;
    }

    return digits == (1 << count) - 1;
}
