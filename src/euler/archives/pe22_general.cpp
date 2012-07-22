/* Using names.txt (pe22.txt) (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file

CHANGES: Placed quicksort into a class in case I ever choose to reuse this implementation, though unlikely
*/

using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

template <class T>
class Sorting {
public:
	typedef typename T::iterator iter;
	typedef typename T::value_type v_type;
	void quicksort(T &items, iter first, iter last) {
		// Base case: return immediately if the list has less than 2 items
		if (last <= first)
			return;

		// Find the pivot location for this set of items
		iter pivot = quicksort_partition_str(items, first, last, (first + distance(first, last) / 2) );

		// Sort items to the left and right of the pivot
		quicksort(items, first, pivot - 1);
		quicksort(items, pivot + 1, last);
	}
private:
	iter quicksort_partition_str(T &items, iter first, iter last, iter pivot) {
		v_type pivot_value = *pivot;
		
		// Move pivot value off to the side
		swap(*pivot, *last);

		iter current_storage_index = first;

		// Iterate through items, placing all items less than the pivot to its left
		for (iter i = first; i < last; i++) {
			if ((*i).compare(pivot_value) < 0) {
				swap(*i, *current_storage_index);
				current_storage_index++;
			}
		}

		// Swap pivot back to center and return its location
		swap(*current_storage_index, *last);
		return current_storage_index;
	}
};

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
	Sorting<vector<string> > s;
	s.quicksort(names_vector, names_vector.begin(), names_vector.end() - 1);
	
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
