/*********************************************************
Project Euler 39 (pe39.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value b <= 1000 is the number of solutions maximised?

NOTES
Using the parameterization of a pythagoren triple a^2 + b^2 = c^2:
a + b + c = p = 2m(m + n) * d;
2m(m+n) produces a primitive triple
If we let (m + n) * m * d = p /2,
then we need to find (m * n) and m such that p / 2 is divisible by both -- then we have one solution

Since n < m; n + m < (m + m), m < (n + m) < 2m
2 < m < sqrt(p / 2)

~ gcd(m, n) = 1 (coprime; one is odd, one is even)
*********************************************************/

#include <iostream>
#include <cmath>

const int kPLimit = 1000;

int main() {
    int solutions_max = 0;
    int p_solution = 0;
    
    // Find the number of solutions for each perimeter 
    for (int p = 12; p <= kPLimit; p += 2) {
        int p_half = p / 2;
        int solutions_current = 0;
        for (int m = 2; m < ceil(sqrt(p_half)); m++) {
            for (int k = m + 1; k < (2 * m); k += 2) {
                // Check that m and (k = (m * n)) divide (p /2)
                if (p_half % m == 0 && (p_half / m) % k == 0)
                    solutions_current++;
            }
        }

        if (solutions_current > solutions_max) {
            solutions_max = solutions_current;
            p_solution = p;
        }
    }

    std::cout << p_solution << std::endl;
}

  
