/* You are given the following information, but you may prefer to do some research for yourself.

    1 Jan 1900 was a Monday.
    Thirty days has September,
    April, June and November.
    All the rest have thirty-one,
    Saving February alone,
    Which has twenty-eight, rain or shine.
    And on leap years, twenty-nine.
    A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

/* NOTES:
1. Constraint: First day of each month
2. Only have to check Sunday
3. Check with Zeller's congruence */

using namespace std;
#include <iostream>

enum days_t {
	saturday = 0, sunday, monday, tuesday, wednesday, thursday, friday
};

int day_for(int date, int month, int year);

int main() {
	int sundays = 0;
	for (int year = 1901; year <= 2000; year++) {
		for (int month = 1; month <= 12; month++) {
			if (day_for(1, month, year) == sunday)
				sundays += 1;
		}
	}
	
	cout << sundays << endl;
}

int day_for(int date, int month, int year) {
	// In Zeller's congruence, Jan/Feb are month "13 and 14" of the previous year
	if (month <= 2) {
		year -= 1;
		month += 12;
	}
	int k = year % 100;
	int j = year / 100;
	int day_of_week = (date + (13 * (month + 1))/5 + k + (k / 4) + (j / 4) + 5 * j) % 7;
	
	return day_of_week;
}