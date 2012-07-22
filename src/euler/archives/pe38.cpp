/*********************************************************
Project Euler 38 (pe38.cpp)
Created by Louis Li on 2012-01-06.

PROBLEM
Take the number 192 and multiply it by each of 1, 2, and 3:

    192 × 1 = 192
    192 × 2 = 384
    192 × 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?

NOTES
We can narrow down the search space by a lot. Given a the list of (1, 2, ... n), the different possibilities of n are limited to certain x for forming a pandigital 1 to 9.
n = 2 => x [5000, 10000)
n = 3 => x [100, 334)
n = 4 => x [25, 34)

This is based on the possibility of multiplying the first number by n and concatenating to reach a 9 digit number.
*********************************************************/

#include <iostream>
#include <map>
#include <stdint.h>

int64_t concatenate(const int64_t a, const int64_t b);
bool is_pandigital(const int64_t n);

typedef std::map<int, std::pair<int, int> > map_range;
typedef std::pair<int, std::pair<int, int> > n_range;
typedef std::pair<int, int> ipair;

int main() {

  int64_t solution = 0;

  // Load the ranges for each n as a map
  map_range ranges;
  ranges.insert(n_range(2, ipair(5000, 10000)));
  ranges.insert(n_range(3, ipair(100, 334)));
  ranges.insert(n_range(4, ipair(25, 34)));

  // Iterate over the range for each key
  for (map_range::iterator i = ranges.begin(); i != ranges.end(); i++) {
    for (int cand = i->second.first; cand < i->second.second; cand++) {
      // Perform the concatenation for each multiple of candidate
      int concatenation = -1;
      for (int n = 1; n <= i->first; n++) {
	concatenation = concatenate(concatenation, cand * n);
      }
  
      // If the concatenation is pandigital, record it
      if (is_pandigital(concatenation)) {
	solution = std:: max<int64_t>(solution, concatenation);
      }
    }
  }

  std::cout << solution << std::endl;
  
}

// Returns the non-negative number if either candidate is negative
// Otherwise returns the concatenation of the two numbers
// Throws an exception upon overflow
int64_t concatenate(const int64_t a, const int64_t b) {
  // Handle negative input
  if (a < 0 && b < 0)
    throw "Exception: concatenating two negative numbers";
  if (a < 0 || b < 0)
    return std::max<int64_t>(a, b);
  
  // Concatenate the two numbers by adding the second number to the first * pow(10, d)
  int64_t x = a, y = b;
  for ( ; y != 0; y /= 10)
    x *= 10;
  return (x + b);
}

// Checks if a number is pandigital 1 to 9
bool is_pandigital(const int64_t n) {
  unsigned char bitmap_n = 0;
  int count = 0;
  for (int64_t num = n; num != 0; num /= 10, count++) {
    // Mark the corresponding bit for the last digit on the bitmap
    bitmap_n = (bitmap_n | (1 << (num % 10 - 1)));
  }

  // Return whether the bitmap is all filled with 1s
  return bitmap_n == (unsigned char)( (1 << count) - 1);
}






