/* The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:

    F1 = 1
    F2 = 1
    F3 = 2
    F4 = 3
    F5 = 5
    F6 = 8
    F7 = 13
    F8 = 21
    F9 = 34
    F10 = 55
    F11 = 89
    F12 = 144

The 12th term, F12, is the first term to contain three digits. */

/* NOTES
n = ((digits - 1) + (log(5) / 2)) / log(phi)
ceil(n) yields the first value of n with `digits` digits
*/ 

using namespace std;
#include <gmpxx.h>
#include <iostream>
#include <cmath>

int main() {
	const int digits = 1000;
	
	// Initialize phi and compute the n for which the nth fib has 1000 digits
	const double phi = (1 + sqrt(5)) / 2;
	int n = ceil((digits - 1 + log10(5)/2.0) / log10(phi));	
	cout << n << endl;
	
	// Compute fib_n (completely optional -- testing library)
	// Seems that the precision would be off by a lot when calculating with floats
	mpf_class fib_n;
	mpf_class mpf_phi(phi);
	mpf_pow_ui(fib_n.get_mpf_t(), mpf_phi.get_mpf_t(), n);
	fib_n = fib_n / sqrt(5) + 0.5;
	
	mpz_class fib_n_floor = floor(fib_n);
	cout << fib_n_floor.get_str() << endl;	
}