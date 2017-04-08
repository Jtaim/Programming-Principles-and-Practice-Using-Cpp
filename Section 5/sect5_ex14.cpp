//written by Jtaim
//date 8 Apr 2017
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
	std::vector<std::pair<std::vector<int>, std::string>> d {
	{ {},"Sunday" },
	{ {},"Monday" },
	{ {},"Tuesday" },
	{ {},"Wednesday" },
	{ {},"Thursday" },
	{ {},"Friday" },
	{ {},"Saturday" }
	};
};
int sum(std::pair<std::vector<int>, std::string> &day_values) {
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

int handle_input(std::string, int, days&);

int main()
try
{
	using std::cout;
	using std::cin;

	days weekdays;
	std::string day;
	int value{ 0 };
	int rejects{ 0 };
	cout << "Enter days of the week (ex:Mon or Monday) and a value. Enter q to exit\n";
	bool escape{ true };
	while (escape)
	{
		cin >> day;
		if (day == "q") {
			escape = false;
		}
		if (escape) {
			if (!(cin >> value)) {
				escape = false;
				error("Got some bad input day values.\n");
			}
			else {
				rejects += handle_input(day, value, weekdays);
			}
		}
		//print the results
		if (!escape)
		{
			//get vector of pairs from the struct
			for (auto weekday : weekdays.d) {
				cout << weekday.second << " has a sum of " << sum(weekday) << '\n';
			}
			cout << "The number of rejects was " << rejects << "\n\n";
		}
	}
	keep_window_open();
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...)
{
	std::cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

int handle_input(std::string day, int val, days &week)
{
	for (auto& i : day) {
		i = narrow_cast<char>(tolower(i));
	}
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
