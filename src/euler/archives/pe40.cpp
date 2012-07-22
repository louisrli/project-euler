/*********************************************************
Project Euler 40 (pe40.cpp)
Created by Louis Li on 2012-01-10.

PROBLEM
An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

NOTES
Goes up to 1e6, let kPow = 6
(Count * numbers) * (digits / number) = digits
Total is 9 * 1 + 99 * 2 + 999 * 3 + 9999 * 4 + 99999 * 5 ... 999 * (kPow + 1)
9 ( 1 + 22 + 333 + 4444 + 55555....)
*********************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <stdint.h>

const int kLimit = 1000000;
const int kPow = 6;

int main() {
  // Concatenate all numbers into a large string
  std::string fraction = "";
  for (int i = 1; i <= kLimit; i++) {
    char i_to_s[kPow + 1 + 1];
    sprintf(i_to_s, "%d", i);
    fraction += i_to_s;
  }

  // Multiply d1...d10 etc
  uint64_t solution = 1;
  for (int i = 1; i <= kLimit; i *= 10)
    solution *= fraction[i - 1] - '0';

  std::cout << solution << std::endl;
}
