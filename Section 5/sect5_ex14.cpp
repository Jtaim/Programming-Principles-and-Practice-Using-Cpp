//written by Jtaim
//date 8 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 14
read (day-of-the-week,value) pairs, collect values for each day in a separate vector.
Ignore illegal days, but accept common synonyms.
escape by "q 5" for day value entry
Print sum and list of values for each day when there is no more input
count of and output rejected entries.
*/

#include "section5.h"

struct days {
	vector<pair<vector<int>, string>> d{
	{ {},"Sunday" },
	{ {},"Monday" },
	{ {},"Tuesday" },
	{ {},"Wednesday" },
	{ {},"Thursday" },
	{ {},"Friday" },
	{ {},"Saturday" }
	};
};
int sum(pair<vector<int>, string> &day_values) {
	int sum{ 0 };
	for (auto i : day_values.first) {
		if ((i > 0) && (sum > INT_MAX - i)) {
			error("int max overflow error");
		}
		if ((i < 0) && (sum < INT_MAX - i)) {
			error("int min overflow error");
		}
		sum += i;
	}
	return sum;
}

int handle_input(string, int, days&);

int main()
try 
{
	days weekdays;
	string day{};
	int value{ 0 };
	int rejects{ 0 };
	cout << "Enter days of the week and a value. Enter q to exit\n";
	bool escape{ true };
	while (escape) {
		cin >> day;
		if (day == "q") {
			escape = false;
		}
		if (escape) {
			cin >> value;
			if (cin.bad() || cin.eof() || cin.fail()) {
				escape = false;
				error("Got some bad input day values.\n");
			}
			else {
				rejects += handle_input(day, value, weekdays);
			}
		}
		if (!escape) { //print the results
			for (auto weekday : weekdays.d) { //get vector of pairs from the struct
				cout << weekday.second << " has a sum of " << sum(weekday) << '\n';
			}
			cout << "The number of rejects was " << rejects << "\n\n";
		}
	}
	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

int handle_input(string day, int val, days &week)
{
	for (string::size_type i = 0; i < day.size(); ++i)
		tolower(day[i]);
	if (day == "sunday" || day == "sun") {
		week.d[0].first.push_back(val);
	}
	else if (day == "monday" || day == "mon") {
		week.d[1].first.push_back(val);
	}
	else if (day == "tuesday" || day == "tue") {
		week.d[2].first.push_back(val);
	}
	else if (day == "wednesday" || day == "wed") {
		week.d[3].first.push_back(val);
	}
	else if (day == "thursday" || day == "thu") {
		week.d[4].first.push_back(val);
	}
	else if (day == "friday" || day == "fri") {
		week.d[5].first.push_back(val);
	}
	else if (day == "saturday" || day == "sat") {
		week.d[6].first.push_back(val);
	}
	else {
		return 1;
	}
	return 0;
}