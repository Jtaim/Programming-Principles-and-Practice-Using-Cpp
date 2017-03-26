//written by Jtaim
//date 25 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.1.1
program that converts yen, euros, and pounds into dollars
*/

#include "section4.h" //custom header

int main()
{
	using namespace std;

	constexpr double yen_to_dollar = 111.33;  //to a dollar
	constexpr double euro_to_dollar = 0.93;
	constexpr double pound_to_dollar = 0.8;

	double amount{ 1.0 };
	string currency{ "???" };
	cout << "Please enter an amount followed by a currency to convert to dollar:\n";
	cout << "yen, euro, or pound\n";

	if (!(cin >> amount)) { simple_error("Incorrect amount entry\n"); }
	cin >> currency;

	if (currency == "yen") {
		cout << amount << " " << currency << " == $"
			 << 1 / yen_to_dollar * amount << endl;
	}
	else if (currency == "euro") {
		cout << amount << " " << currency << " == $"
			 << 1 / euro_to_dollar * amount << endl;
	}
	else if (currency == "pound") {
		cout << amount << " " << currency << " == $"
			 << 1 / pound_to_dollar * amount << endl;
	}
	else {
		cout << "Sorry, I don't know a currency called " << currency << endl;
	}
	keep_window_open();
	return 0;
}
