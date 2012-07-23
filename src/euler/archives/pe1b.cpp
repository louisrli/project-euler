#include <iostream>

using namespace std;

int main() {
	float sum = 0;
	float three = (3 + 999)/2.0 * (333);
	float five = (5 + 995)/2.0 * (199);
	float fifteen = (15 + 990)/2.0 * (66);
	
	sum = three + five - fifteen;
	
	cout << sum << endl;
}