/* Euler published the remarkable quadratic formula:

n² + n + 41

It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

Using computers, the incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

    n² + an + b, where |a| < 1000 and |b| < 1000

    where |n| is the modulus/absolute value of n
    e.g. |11| = 11 and |−4| = 4

Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0. */

/* NOTES
Because the answer asks for consecutive primes starting at n = 0:
a. Constraint: b > 0; b is prime (0 + 0 + b) = b -> must be a prime number AND b must be positive
	b. Let f(n) = n^2 + an + b; when n = 1; f(n) = 1 + a + b; f(n) is prime -> f(n) > 0. Therefore a > -b - 1 = - (b + 1)
*/
	
using namespace std;
#include <iostream>
#include "euler.h"

const int kLimit_a = 1000;
const int kLimit_b = 1000;

long long f_n(int n, int a, int b);

int main() {
	int prod_ab = 0;
	int current_max = 0;
	
	PrimeSieve sieve(100000);
	vector<long long> primes = sieve.getPrimes();
	
	for (int i = 0; primes[i] < kLimit_b; i++) {
		int b = primes[i];
		for (int a = (-1) * b; a < kLimit_a; a++) {
			// Find the number of conseuctive values of n that yield primes
			int n = 0;
			for (; sieve[f_n(n, a, b)] == true; n++);
			
			// Record the new maximum consecutive and the product of coefficients
			if (n > current_max) {
				prod_ab = a * b;
				current_max = n;
			}
		}
	}
	cout << prod_ab << endl;
}

long long f_n(int n, int a, int b) {
	return (n * n) + a * n + b;
}