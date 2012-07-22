/*********************************************************
Project Euler 31 (pe31.cpp)
Created by Louis Li on 2012-01-03.

PROBLEM
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

    1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).

It is possible to make £2 in the following way:

    1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

How many different ways can £2 be made using any number of coins?

NOTES

*********************************************************/

using namespace std;
#include <iostream>
#include <vector>

const int kDenoms[] = {25, 10, 5};
const int kDenomsCount = sizeof(kDenoms) / sizeof(int);
const int kPence = 300;

long long find_combos(int remaining, int denom_index);

int main() {
	cout << find_combos(kPence, 0) << endl;
}

long long find_combos(int remaining, int denom_index) {
	// Base cases: fill in the rest with 1s OR no remainder (200 pence filled)
	if ((remaining > 0 && denom_index == kDenomsCount - 1) || remaining == 0)
		return 1;

	// Recursively test each number of current denomination, switching to the NEXT denomination
	int current_value = kDenoms[denom_index];
	int combos = 0;
	// cout << "Current Coin: " << current_value << " " << "Remaining: " << remaining << endl;
	for (int j = 0, n = (remaining / current_value) + 1; j < n; j++)
		combos += find_combos(remaining - (current_value * j), denom_index + 1);
	return combos;
}
