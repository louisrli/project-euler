/* If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. 
For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
The use of "and" when writing out numbers is in compliance with British usage. */

/* NOTES
Listing out cases that need to be handled
a. Digits: 1-9
b. Tens: 10, 20, 30..
c. Tens + digits: twenty one, thirty two, forty four, etc.
d. Hundreds: 100, 200, 300
c. Hundreds + tens: one hundred and ten, one hundred and twelve
d. Hundreds + tens + digits: one hundred and twenty two

*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// prefixes 
const string digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const string tens[9] = {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

// unique cases
const string n_teens[9] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

// precalculate length for repeated literals
const int hundred_length = strlen("hundred");
const int and_length = strlen("and");
const int thousand_length = strlen("thousand");

int main() {
	int sum = 0;
	
	// Initialize a cache for the first one hundred numbers
	// vector[n] yields the length of n, not n - 1
	vector<int> cached_lengths;
	cached_lengths.resize(100);
	
	// Add and cache lengths of the first 99 numbers
	for (int i = 1; i <= 99; i++) {
		// Handle exact tens
		if (i % 10 == 0) {
			string tens_string = tens[(i / 10) - 1];
			cached_lengths[i] = tens_string.length();
			sum += cached_lengths[i];
		}
		
		// Handle digits
		else if (i < 10) {
			string digits_string = digits[i - 1];
			cached_lengths[i] = digits_string.length();
			sum += cached_lengths[i];
		}
		
		// Handle n-teens
		else if (10 < i && i < 20) {
			string n_teens_string = n_teens[i - 10 - 1];
			cached_lengths[i] = n_teens_string.length();
			sum += cached_lengths[i];
		}
		
		// Everything else, taken from cache
		// Tens will have been cached
		else {
			int tens_value = i / 10 * 10;
			int digits_value = i % 10;
			cached_lengths[i] = cached_lengths[tens_value] + cached_lengths[digits_value];
			sum += cached_lengths[i];
		}
	}
	
	for (int j = 100; j < 1000; j++) {
		// All numbers from here have digit + hundred
		sum += (hundred_length + cached_lengths[j / 100]);

		// Move on if this is an exact one hundred
		if (j % 100 == 0)
			continue;
		
		// Handle exact hundreds and tens - "one hundred and twenty"
		else if (j % 10 == 0) {
			int tens_value = (j % 100);
			sum += (and_length + cached_lengths[tens_value]);
		}
		
		// Handle in-between cases using cached lengths
		else {
			sum += (and_length + cached_lengths[j % 100]);
		}

	}
	
	// Handle 1000
	sum += cached_lengths[1] + thousand_length;
	
	cout << sum << endl;
}

/* Ending note: possible optimizations include precalculating the number of times that "hundred" appears  (899) (minor)
or doing 100 * lengthof("one") for one hundred and all of the other two hundreds, but would've ruined the modularity in the code (e.g. iterate through 1-99 then 100-1000 linearly) */
