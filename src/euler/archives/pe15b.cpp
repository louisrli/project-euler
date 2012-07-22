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

const int length = 1000;

using namespace std;
#include <iostream>	
#include <map>
#include <string>
#include <sstream>

unsigned long long move(int x, int y);

map<string, unsigned long long> cachedResults;

int main() {
	unsigned long long paths = 0;
	paths = move(0, 0);
	cout << paths  << endl;
}

unsigned long long move(int x, int y) {
	// Create a joint-key for whatever is left, checking if the remaining block has already been calculated
	stringstream stream_one, stream_two;
	string remaining_block, reverse_block;
	
	stream_one << length - x << "." << length - y;
	stream_one >> remaining_block;
	stream_two << length - y << "." << length - x;
	stream_two >> reverse_block;
	
	if (x == length || y == length)
		return 1;
	
	unsigned long long current_paths = 0;
	if (cachedResults.count(remaining_block) == 0 || cachedResults.count(reverse_block) == 0)
	{
		if (x == length && y == length) {
			current_paths += 1;
		}
		if (x < length) {
			current_paths += move(x + 1, y);
		}
		if (y < length) {
			current_paths += move (x, y + 1);
		}
		
		cachedResults.insert(pair<string, unsigned long long>(remaining_block, current_paths));
		cachedResults.insert(pair<string, unsigned long long>(reverse_block, current_paths));
	}
	return cachedResults[remaining_block];
}