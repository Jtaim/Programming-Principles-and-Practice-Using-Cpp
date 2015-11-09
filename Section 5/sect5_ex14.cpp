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

bool handle_input(string, int, int&, days&);
void print_results(const int, const days&);

int main()
try 
{
	bool escape{ true };
	days weekdays;
	string day{};
	int value{ 0 };
	int rejects{ 0 };
	cout << "Enter days of the week and a value. Enter q 5 to exit\n";
	while (escape) {
		cin >> day >> value;
		if (cin.good()) {
			escape = handle_input(day, value, rejects, weekdays);
			if (!escape) {
				print_results(rejects, weekdays);
			}
		}
		else  // something bad was entered
			escape = false;
	}
	if (cin.fail()) {
		error("Got some bad input.\n");
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

bool handle_input(string day, int val, int &rejected, days &week)
{
	bool condition{ true };
	for (string::size_type i = 0; i < day.length(); ++i)
		tolower(day[i]);
	if (day == "sunday" || day == "sun")
		week.d[0].first.push_back(val);
	else if (day == "monday" || day == "mon")
		week.d[1].first.push_back(val);
	else if (day == "tuesday" || day == "tue")
		week.d[2].first.push_back(val);
	else if (day == "wednesday" || day == "wed")
		week.d[3].first.push_back(val);
	else if (day == "thursday" || day == "thu")
		week.d[4].first.push_back(val);
	else if (day == "friday" || day == "fri")
		week.d[5].first.push_back(val);
	else if (day == "saturday" || day == "sat")
		week.d[6].first.push_back(val);
	else if (day == "q" && val == 5)
		condition = false;
	else ++rejected;
	return condition;
}
void print_results(const int rej, const days &wds)
{
	for (auto weekday : wds.d) { //get to vector from the struct
		cout << weekday.second << " has a sum of "; // second in the pair is the name of the day
		int sum = 0;
		for (auto values : weekday.first) { // get to the vector holding numbers for the day
			sum += values;
		}
		cout << sum << '\n';
	}
	cout << "the number of rejects was " << rej << "\n\n";
	cout << "what a long trip it has been.\n";
	return;
}
