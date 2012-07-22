/*Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

    1634 = 14 + 64 + 34 + 44
    8208 = 84 + 24 + 04 + 84
    9474 = 94 + 44 + 74 + 44

As 1 = 14 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits. */

/* NOTES
Most pattern finding done by hand, but four digit / five digit numbers are all viable. However, four digit numbers are very limited and cannot contain 7-9
*/

using namespace std;

#include <iostream>
#include <cmath>
#include <vector>

const int kDigits = 10;
const int kPower = 5;

int sum_of_fifths(const int num, vector<int> &cached_powers);

int main() {
	long long sum = 0;
	
	// Cache the values of fifth powers to prevent repeated calculations
	vector<int> fifth_powers(kDigits, 0);
	for (int i = 0; i < kDigits; i++)
		fifth_powers[i] = pow(i, kPower);
	
	// Check if the sum of the fifth powers equals the number up until a limit of 999999's sum
	for (int i = 1000; i < 6 * fifth_powers[9]; i++) {
		if (sum_of_fifths(i, fifth_powers) == i)
			sum += i;
	}
	
	cout << sum << endl;
}

// Finds the sum of the fifth powers of the digits in a number
int sum_of_fifths(const int num, vector<int> &cached_powers) {
	int parsed_num = num;
	int sum = 0;
	while (parsed_num != 0) {
		// Destructively grab the last digit
		int digit_last = parsed_num % 10;
		sum += cached_powers[digit_last];
		parsed_num /= 10;
	}	
	return sum;
}