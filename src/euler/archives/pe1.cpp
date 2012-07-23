#include <iostream>
#include <numeric>

using namespace std;

// Declare constants
const unsigned int ceiling = 1000;
const unsigned int a = 3;
const unsigned int b = 5;
const unsigned int c = a * b;

int main() {
	unsigned int sum = 0;
	
	// Calculate the sum of multiples for a and b
	for (int i = 1, n = (ceiling - 1)/ a; i <= n; i++)
		sum += (i * a);
	for (int i = 1, n = (ceiling - 1)/ b; i <= n; i++)
		sum += (i * b);
	
	// Subtract the coinciding terms
	for (int i = 1, n = (ceiling - 1)/c; i <= n; i++) 
		sum -= (i * c);
	
	cout << sum << endl;
}