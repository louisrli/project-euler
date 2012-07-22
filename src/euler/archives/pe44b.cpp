/*********************************************************
Project Euler 44 (pe44.cpp)
Created by Louis Li on 2012-01-11.

PROBLEM
Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2. The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference, 70 − 22 = 48, is not pentagonal.

Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference is pentagonal and D = |Pk − Pj| is minimised; what is the value of D?

NOTES
Most work done by hand
Three things to consider: how to find the cap, and how to iterate through pentagonal numbers efficiently, and how to test
A number x is pentagonal if (sqrt(24x + 1) + 1) / 6 is a whole number
p_n = (3n^2 - n) / 2 generates the pentagonal numbers
Using this equation for p_n and p_(n+g), we find generalized equations
for the sum and difference of pentagonal numbers with a certain gap
Difference: 1 + 3gn
Sum: 3n^2 + n(3g - 1) + (3g^2 - g)/2

Let C be the condition that the sum and difference of Pj and Pk are pentagonal
For a gap g, sum(Pj, P_(j+g)) and difference(Pj, P_(j+g)) <  P_(j+1) ...
We assume there is a P_n that satifies C for g = 1, and let their difference be D
Then we search g = 2 for a pair that satisfies C until their difference > D
Search g = 3, 4...k until the difference (P_(g + 1) - P_1) > D, then stop
*********************************************************/

#include <iostream>
#include <cmath>
#include <stdint.h>

bool is_pentagonal(int x);
bool is_perf_square(int64_t n);
uint64_t pentagonal_sum(uint64_t n, int gap);
uint64_t pentagonal_diff(uint64_t n, int gap);

int main() {
    uint64_t solution = 0;
    // Search for the one gap, baseline differences
    for (int n = 1; n < 2000; n++) {
        for (int gap = 1; gap < 1148; gap++) {
            uint64_t p_diff = pentagonal_diff(n, gap), p_sum = pentagonal_sum(n, gap);
            if (is_pentagonal(p_diff) && is_pentagonal(p_sum)) {
                solution = (solution == 0) ? p_diff : std::min<uint64_t>(p_diff, solution);
            }
        }
    }
    std::cout << solution << std::endl;
    return 0;
}

// If (sqrt(24x+1) + 1)/6 is a natural number, x is pentagonal
bool is_pentagonal(int x) {
    if (!is_perf_square(24 * x + 1))
        return false;
    int numerator = static_cast<int>(floor(sqrt(24 * x + 1) + 0.5)) + 1;
    return numerator % 6 == 0;
}

// Computes the sum of p_n and p_(n + gap)
uint64_t pentagonal_diff(uint64_t n, int gap) {
    return (6 * gap * n + 3 * gap * gap - gap) / 2;
}

// Computes the difference of p_(n + gap) and p_n
uint64_t pentagonal_sum(uint64_t n, int gap) {
    return (3 * n * n) + n * (3 * gap - 1) + (3 * gap * gap - gap) / 2;
}

// Returns whether n is a perfect square, ruling out certain digits
// Adapted from John D. Cook's post, StackOverflow
bool is_perf_square(int64_t n) {
    int unit = (n & 0xF);
    if (unit > 9 || (unit != 1 && unit != 4 && unit != 9 && unit != 0))
        return false;

    int root = static_cast<int64_t>(floor(sqrt(n) + 0.5));
    return (root * root == n);
}
