/* By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
3
7 4
2 4 6
8 5 9 3
That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:
[ pe18.txt ]
NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
*/

/* NOTES
a. Adjacent numbers only
b. Is an overlapping binary search tree
c. Store triangle in vector
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdio>

using namespace std;

const int kRows = 15;

int triangle_step(int row, int index, int sum, const vector <vector<int> > &triangle);

int main() {
	vector<vector <int> > triangle(kRows);
	// Load triangle file into a two dimensional vector
	ifstream file_triangle("pe18.txt");
	if (!file_triangle.is_open() ) {
		cout << "Error opening file." << endl;
		return -1;
	}
	
	// Configure triangle and load row information
	for (int i = 0; i < kRows; i++) {
		triangle[i].resize(i + 1);		
		for (int j = 0; j < i + 1; j++) {
			if (file_triangle.good() )
				file_triangle >> triangle[i][j];
		}
	}
	file_triangle.close();

	int sum = triangle_step(0, 0, 0, triangle);	
	cout << sum << endl;
}

int triangle_step(int row, int index, int sum, const vector<vector<int> > &triangle)
{
	// Prepare the string representation of location
	static map<string, int> cached_sums;
	char location_cstr[10];
	sprintf(location_cstr, "r%di%d", row, index);
	string key = location_cstr;
	
	sum += triangle[row][index];
	
	// Check if this location is already in cache
	if (cached_sums.find(key) != cached_sums.end() )
		return sum + cached_sums[key];

	
	// End condition - return the sum if function has reached end
	if (row == kRows - 1) {
		return sum;
	}
	
	// Otherwise get the maximum sum for the next two branches
	int left_result = triangle_step(row + 1, index, sum, triangle);
	int right_result = triangle_step(row + 1, index + 1, sum, triangle);
	int max_num = max(left_result, right_result);
	
	// Cache the greatest sum from this location forward and return
	cached_sums.insert(pair<string, int>(key, max_num - sum));
	return max_num;
}