/* 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20? */

/* NOTES
* 1. Max is prod[1...20]
* 2. The answer must be a multiple of 2520 (LCM[1..10])
*/

using namespace std;
#include <iostream>

int main()
{
	const int cap = 20;
	const int base_lcm = 2520;
	
	for (int j = 11; j <= base_lcm * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18 * 19 * 20; j++)
	{
		bool numberFound = true;
		int candidateNum = j * base_lcm;
		for (int i = 11; i <= cap; i++)
		{
			if (candidateNum / i * i != candidateNum)
			{
				numberFound = false;
			}
		}
		if (numberFound)
		{
			cout << candidateNum << endl;
			return 1;
		}
		
	}
	
}
