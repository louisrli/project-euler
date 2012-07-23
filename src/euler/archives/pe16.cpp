/* 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000? */


using namespace std;
#include <iostream>	
#include <vector>
#include <numeric>
#include <cassert>

const int power = 1000;

// Overview: a vector container stores the power in reverse order (not relevant for digit adding)

int main() {
	vector<int> container;
	container.push_back(1);
	
	// Compute 2^1000 by multiplying each digit by two
	for (int i = 0; i < power; i++) {
		// First pass: multiply digits by two
		for (int j = 0, n = container.size(); j < n; j++)
			container[j] *= 2;
		
		// Second pass: carry over any digits, simulating multiplication by hand
		for (int j = 0, n = container.size(); j < n; j++) {
			// If exceeds ten, "carry over" by adding one to the next slot
			if (container[j] >= 10) {
				// Create a new digit slot if needed
				if (j == (n - 1))
					container.push_back(0);
				
				// Decrease the old container and carryover to the new slot
				container[j] -= 10;
				container[j + 1] += 1;
			}
				
			// Value of a vector slot should never be greater than ten
			assert(container[j] < 10);
		}
	}
		
	// Find the sum of all of the digits
	unsigned long long solution = accumulate(container.begin(), container.end(), 0);
	cout << "Solution: " << solution << endl;
}