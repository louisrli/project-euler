/* Starting in the top left corner of a 2×2 grid, there are 6 routes (without backtracking) to the bottom right corner.

How many routes are there through a 20×20 grid?
*/

/* NOTES
1. The length of the no-backtrack path for a L x L grid is L + L (traverse height once, traverse width)
2. At each path, there are two options (right or down)
4. Goal length: (L + L steps). How many ways can you make L + L steps with either two or one at each step?
5. That means L + L (40) decision points, with two possibilities at each one EXCEPT on the right or bottom edges
6. 

*/

const int length = 2;

using namespace std;
#include <iostream>	

void move(int x, int y, long long &current_paths);

int main() {
	long long paths = 0;
	move(0, 0, paths);
	cout << paths  << endl;
}

void move(int x, int y, long long &current_paths) {
	if (x == length && y == length) {
		current_paths += 1;
		return;
	}
	if (x < length) {
		move(x + 1, y, current_paths);
	}
	if (y < length ) {
		move (x, y + 1, current_paths);
	}
}