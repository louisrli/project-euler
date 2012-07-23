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
	string container = "";
	// Add and cache lengths of the first 99 numbers
	for (int i = 1; i <= 99; i++) {
		// Handle exact tens
		if (i % 10 == 0)
			container += tens[(i / 10) - 1];
		// Handle digits
		else if (i < 10) 
			container += digits[i - 1];
		// Handle n-teens
		else if (10 < i && i < 20)
			container += n_teens[i - 10 - 1];
		// Everything else
		else {
			container += tens[(i / 10) - 1];
			container += digits[(i % 10) - 1];
		}
	}
	
	for (int j = 100; j < 1000; j++) {
		// All numbers from here have digit + hundred
		container += digits[(j / 100) - 1];
		container += "hundred";
		
		// Move on if this is an exact one hundred
		if (j % 100 == 0)
			continue;
		
		// Handle exact hundreds and tens - "one hundred and twenty"
		else if (j % 10 == 0) {
			container += "and";
			container += tens[((j % 100) / 10) - 1];
		}
		
		// Handle in-between cases using cached lengths
		else {
			container += "and";
			// n-teens
			if (10 < j % 100 && j % 100 < 20) {
				container += n_teens[(j % 10) - 1];
			}
			// digits
			else if (j % 100 < 10) {
				container += digits[(j % 10) - 1];
			}
			// everything else
			else {
				container += tens[((j % 100) / 10) - 1];
				container += digits[(j % 10) - 1];
			}
		}

	}
	// Handle 1000
	container += "onethousand";
	
	cout << container.length() << endl;
}
