/* The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ? */

// Notes
// The largest number to check is target / 3

using namespace std;
#include <iostream>
#include <cmath>

typedef unsigned long long ull;

bool isPrime(ull x);
bool isPerfSquare(ull x);


int main() 
{
	ull target = 600851475143;
	
	ull solution = 0;
	ull a = ceil(sqrt((long double) target));
	ull n = (target / 3) + 1;
	cout << "long double target : " << a << endl;
	
	
	while (a <= n)
	{
		ull b_squared = a * a - target;
		if (isPerfSquare(b_squared))
		{
			ull b = (ull) (sqrt((long double) b_squared) + 0.5);
			if ((a + b > solution) && isPrime(a + b))
			{
				solution = a + b;
				cout << "** Potential solution: **" << solution << endl;
			}
			else if ((a - b > solution) && isPrime(a - b))
			{
				solution = (a - b);
				cout << "** Potential solution: ** " << solution << endl;
			}
		}
		a++;
	}
	cout << solution << "\n";
}

bool isPrime(ull x)
{
	ull a = ceil(sqrt((long double) x));
	ull n = (x / 3) + 1;
	
	while (a <= n)
	{
		ull b_squared = a * a - x;
		if (isPerfSquare(b_squared))
		{
			ull b = (ull) (sqrt((long double) b_squared) + 0.5);
			if (((a + b) != x) || ((a + b) != 1))
			{
				cout << "returning false for primality of " << x << endl;
				return false;
			}
		}
		a++;
	}
	cout << "returning true for primality of " << x << endl;
	return true;
}

bool isPerfSquare(ull x)
{
	ull n = (ull) (sqrt((long double) x) + 0.5);
	return (n * n == x);
}