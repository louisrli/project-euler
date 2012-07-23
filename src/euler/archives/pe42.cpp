/*********************************************************
Project Euler 42 (pe42.cpp)
Created by Louis Li on 2012-01-10.

PROBLEM
The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?

NOTES
Functions: int word_value(string n), bool is_triangle_number(int n)
A number is a triangular number if 8x + 1 is a square

COMPATIBILITY
pe42.txt was edited to add whitespace between each word
*********************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <stdint.h>

int word_value(std::string s);
bool is_triangle_number(int n);
bool is_perf_square(int64_t n);

int main() {
    int count = 0;
    
    // Load word file
    std::ifstream wordfile("pe42.txt");
    if (!wordfile.is_open()) {
        std::cerr << "There was an error opening pe42.txt" << std::endl;
        return -1;
    }

    // Record whether each word value is a triangle number
    while (wordfile.good()) {
        std::string word;
        wordfile >> word;
        if (is_triangle_number( word_value(word)))
            count++;
    }

    std::cout << count << std::endl;
}

// Computes word value, case-insensitive, from a string
int word_value(std::string s) {
    int sum = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        sum += isalpha(s[i]) ? (tolower(s[i]) - 'a' + 1) : 0;
    }
    return sum;
}

bool is_triangle_number(int n) {
    return is_perf_square(8 * n + 1);
}

// Returns whether a given integer is a perfect square; doesn't count zero
bool is_perf_square(int64_t n) {
    if (n <= 0)
        return false;
    return (static_cast<int64_t>(sqrt(n)) * static_cast<int64_t>(sqrt(n)) == n);
}
