/* Using names.txt (pe22.txt) (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/

using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

void quicksort(vector<string> &items, int first, int last);
int partition_str(vector<string> &items, const int first, const int last, const int pivot_index);
int compute_word_score(const string word);

int main() {
	// Load the strings into a vector from file
	ifstream names_file;
	names_file.open("pe22.txt");
	if (!names_file.is_open() ) {
		cerr << "There was an error opening the file pe22.txt." << endl;
		return -1;
	}
	
	vector<string> names_vector;
	string temp_name;
	while (names_file.good() ) {
		names_file >> temp_name;
		names_vector.push_back(temp_name);
	}
	
	// Sort the strings vector
	quicksort(names_vector, 0, names_vector.size() - 1);
	
	// Compute the score of each string based on position and letters
	int sum = 0;
	
	for (unsigned int i = 0; i < names_vector.size(); i++) {
		sum += ((i + 1) * compute_word_score(names_vector[i]) );
	}
	
	cout << sum << endl;
}

int compute_word_score(const string word) {
	const char *cstr_word = word.c_str();
	unsigned int score = 0;
	
	// Compute case-insensitive score for alphabetical letters only
	for (unsigned int i = 0; i < word.size(); i++) {
		if (isalpha(cstr_word[i]) )
			score += cstr_word[i] % 32;
	}
	return score;
}
void quicksort(vector<string> &items, int first, int last) {
	// Base case: return immediately if the list has less than 2 items
	if (last <= first)
		return;
	
	// Find the pivot location for this set of items
	int pivot_new_index = partition_str(items, first, last, (first + last) / 2);
	
	// Sort items to the left and right of the pivot
	quicksort(items, first, pivot_new_index - 1);
	quicksort(items, pivot_new_index + 1, last);
}

int partition_str(vector<string> &items, const int first, const int last, const int pivot_index) {
	string pivot_value = items[pivot_index];
	// Move pivot index off to the side
	swap(items[pivot_index], items[last]);
	
	int current_storage_index = first;
	
	// Iterate through items, placing all items less than the pivot to its left
	for (int i = first; i < last; i++) {
		if (items[i].compare(pivot_value) <= 0) {
			swap(items[i], items[current_storage_index]);
			current_storage_index++;
		}
	}
	
	// Swap pivot back to center and return its location
	swap(items[current_storage_index], items[last]);
	return current_storage_index;
}