/* A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

/* NOTES
* 1. Identify numbers that are palindromes
*  2. Identify numbers that are multiples of three digit numbers
*  3. Count down, not up
*/



using namespace std;
#include <iostream>

bool isPalindrome(int);

int main () 
{
	// check if each number, going down, is a palindrome
	for (int j = 999 * 999; j >= 10000; j--)
	{
		if (isPalindrome(j))
		{
			for (int i = 999; i >= 100; i--)
			{
				int remainder = j % i;
				int secondDivisor = j / i;
				// check if the number can be fully divided, and the second multiple is a three digit number
				if (remainder == 0 && (secondDivisor >= 100 && secondDivisor <= 999))
				{
					cout << j << endl;
					return 1;
				}
			}
		}
	}
}

// Checks if a number is a palindrome
bool isPalindrome(int n)
{
	// convert product to string
	char *string = (char *)malloc(sizeof(char) * 12);
	sprintf(string, "%d", n);
	int len = strlen(string);
	
	// check if product is palindrome by traversing front and back ends
	for (int i = 0; i < len / 2; i++)
	{
		if (string[i] != string[len - 1 - i])
			return false;
	}
	return true;
}