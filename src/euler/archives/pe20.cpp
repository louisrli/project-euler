/* 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000? */


using namespace std;
#include <iostream>	
#include <vector>
#include <numeric>
#include <cassert>

const int kFactorial = 100;
const int kExpandAmount = 3;
// Overview: a vector container stores the factorial product
int main() {
	vector<int> container;
	container.push_back(1);
	
	for (int i = kFactorial; i >= 1; i--) {
		// First pass: multiply digits by factorial
		for (int j = 0, n = container.size(); j < n; j++)
			container[j] *= i;
		
		// Second pass: carry over any digits, simulating multiplication by hand
		for (int j = 0, n = container.size(); j < n; j++) {
			// If the digit slot exceeds ten, carry it over and expand container if necessary
			if (container[j] >= 10) {
				if (j == (n - 1))
					container.insert(container.end(), kExpandAmount, 0);
				
				// Decrease the old container and carryover to the new slot
				container[j + 1] += container[j] / 10;
				container[j] %= 10;
			}
			
			n = container.size();
			// Value of a vector slot should never be greater than ten
			assert(container[j] < 10);
		}
	}
		
	// Find the sum of all of the digits
	unsigned long long solution = accumulate(container.begin(), container.end(), 0);
	cout << "Solution: " << solution << endl;
}