/* The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million. */

using namespace std;
#include <iostream>

const int limit = 1000000;
int main() {
	int max_chain = 1;
	int answer = 0;
	
	for (int n = 2; n <= limit; n++) {
		// apply to the chain
		int current_chain = 1;
		unsigned int stop = n;
		while (stop != 1) {
			// even
			if (stop % 2 == 0)
				stop /= 2;
			else
				stop = stop * 3 + 1;
			current_chain++;
		}
		
		// record number if it's the current highest
		if (current_chain > max_chain)
			answer = n;
		max_chain = max(current_chain, max_chain);
	}
	
	cout << "Answer: " << answer << endl;
	cout << "Chain length: " << max_chain << endl;
}