/* Work out the first ten digits of the sum of the following one-hundred 50-digit numbers. */

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

const int digits_count = 50;
const int numbers_count = 100;

int main() {	
	// open file with numbers
	ifstream numfile("pe13.txt");
	if (!numfile.is_open())
	{
		cerr << "Could not open the numbers file.";
		return -1;
	}
	
	// store each number in file as a string (a "row" of chars) in the matrix
	char matrix[numbers_count][digits_count + 1];
	int line_index = 0;
	while (numfile.good()) {
		numfile >> matrix[line_index];
		matrix[line_index][digits_count] = '\0';
		line_index++;
	}
	numfile.close();
	
	// perform arithmetic on matrix by summing first 11 columns (13 digit answer; 2 padding)
	int carryover = 0;
	vector<int> starting_digits;
	for (int col = 10; col >= 0; col--) {
		// add the carryover to the new column
		int sum_column = carryover;
			
		for (int row = 0; row < numbers_count; row++) {
			// find the sum of the column
			sum_column += matrix[row][col] - '0';
		}
		
		// calculate the new carryover
		int current_digit = sum_column % 10;
		carryover = sum_column / 10;
		// cout << carryover << " " << current_digit << endl;
		// when getting to the last ten digits, start recording them
		if (col < 10) {
			starting_digits.insert(starting_digits.begin(), current_digit);
		}
	}

	// include the carryover digits
	while (carryover != 0) {
		starting_digits.insert(starting_digits.begin(), carryover % 10);
		carryover /= 10;
	}
	
	// print out the first ten digits
	for (vector<int>::iterator iter = starting_digits.begin(); iter < starting_digits.begin() + 10; iter++)
	{
		cout << *iter;
	}
	cout << endl;
	
}