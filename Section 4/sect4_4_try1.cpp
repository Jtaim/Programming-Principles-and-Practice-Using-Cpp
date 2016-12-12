//written by Jtaim
//date 19 Sept 2015
//updated 4 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.1.1
program that converts yen, euros, and pounds into dollars
*/

#include "section4.h" //custom header

int main()
{
	using namespace std;
	constexpr double yen_to_dollar = 120.36;  //to a dollar
    constexpr double euro_to_dollar = 0.89;
    constexpr double pound_to_dollar = 0.64;
    double amount = 1.0;
    string currency = "???";
    cout<< "Please enter an amount followed by a currency:\n";
    cin >> amount >> currency;

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