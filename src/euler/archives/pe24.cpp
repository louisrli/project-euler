/* A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9? */

/* NOTES:
a. There are 10! permutations
This algorithm generates permutations in lexicographic order: http://en.wikipedia.org/wiki/Permutations#Generation_in_lexicographic_order
*/

using namespace std;
#include <vector>
#include <iostream>

const unsigned int kDigits = 10;
const unsigned int kPermutation = 1000000;

bool next_lex_permutation(vector<int> &permutation);

int main() {
	// Create a vector of digits in minimal lexicographic order (permutation 1)
	vector<int> current_perm(kDigits);
	for (unsigned int i = 0; i < kDigits; i++)
		current_perm[i] = i;

	// Generate permutations in lexicographic order
	for (unsigned int j = 1; j < kPermutation; j++)
		next_lex_permutation(current_perm);
	
	// Print solution
	for (unsigned int i = 0; i < kDigits; i++)
		cout << current_perm[i];
	cout << endl;
}


/* Implementing this algorithm, taken from http://en.wikipedia.org/wiki/Permutations#Generation_in_lexicographic_order:
" 1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
2. Find the largest index l such that a[k] < a[l]. Since k + 1 is such an index, l is well defined and satisfies k < l.
3. Swap a[k] with a[l].
4. Reverse the sequence from a[k + 1] up to and including the final element a[n]."" */
bool next_lex_permutation(vector<int> &permutation) {
	
	unsigned int digits = permutation.size();
	unsigned int k = 0, l = 0;
	
	// Find the indexes k and l
	bool k_found = false;
	for (unsigned int i = 0; i < digits - 1; i++) {
		// Ensure that we're only dealing with single digits for lexicographic order
		if (permutation.at(i) < 0 || 9 < permutation.at(i))
			cerr << "Warning: trying to find the lexicographic permutation with a non-positive digit." << endl;
		
		if (permutation.at(i) < permutation.at(i + 1)) {
			k = i;
			k_found = true;
		}
		
		if (permutation.at(k) < permutation.at(i + 1))
			l = i + 1;
	}
	
	// If k remained unchanged at the out of bounds sentinel value, this is the final permutation
	if (!k_found) 
		return false;
	
	// Swap the values at k and l indices and reverse (k + 1) to th eend
	swap(permutation[k], permutation[l]);
	reverse(permutation.begin() + k + 1, permutation.end() );
	return true;
}