//written by Jtaim
//date 25 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 11.
a program that prompts the user to enter some number of pennies (1-cent coins), 
nickels (5-cent coins), dimes (10-cent coins), quarters (25-cent coins), 
half dollars (50-cent coins), and one-dollar coins (100-cent coins). 
Query the user separately for the number of each size coin, e.g., “How many pennies do you have?” 
Then your program should print out something like this:
You have 23 pennies.
You have 17 nickels.
You have 14 dimes.
You have 7 quarters.
You have 3 half dollars.
The value of all of your coins is 573 cents.
*/

#include "section3.h" //custom header

int main()
{
	using namespace std;

	cout << "Lets count some change $$$$!\n";
	int penny{ 0 };
	int nickel{ 0 };
	int dime{ 0 };
	int quarter{ 0 };
	int half_dollar{ 0 };
	int dollar{ 0 };
	//feel lazy so did not do input checking
	cout << "Enter number of pennies: ";
	cin >> penny;
	cout << "Enter number of nickels: ";
	cin >> nickel;
	cout << "Enter number of dimes: ";
	cin >> dime;
	cout << "Enter number of quarters: ";
	cin >> quarter;
	cout << "Enter number of half dollars: ";
	cin >> half_dollar;
	cout << "Enter number of dollar coins: ";
	cin >> dollar;

	string denomination{ "???" };
	if (penny > 0) {
		denomination = (penny == 1 ? "penny" : "pennies");
		cout << "you have " << penny << " " << denomination << endl;
	}

	if (nickel > 0) {
		denomination = (nickel == 1 ? "nickel" : "nickels");
		cout << "you have " << nickel << " " << denomination << endl;
	}

	if (dime > 0) {
		denomination = (dime == 1 ? "dime" : "dimes");
		cout << "you have " << dime << " " << denomination << endl;
	}

	if (quarter > 0) {
		denomination = (quarter == 1 ? "quarter" : "quarters");
		cout << "you have " << quarter << " " << denomination << endl;
	}

	if (half_dollar > 0) {
		denomination = (half_dollar == 1 ? "half dollar" : "half dollars");
		cout << "you have " << half_dollar << " " << denomination << endl;
	}

	if (dollar > 0) {
		denomination = (dollar == 1 ? "dollar" : "dollars");
		cout << "you have " << dollar << " " << denomination << endl;
	}

	double total{ 0.0 };
	total = penny + nickel * 5 + dime * 10 + quarter * 25 + half_dollar * 50 + dollar * 100;
	total /= 100;
	cout << "your total is $" << total << endl;

	keep_window_open();
	return 0;
}
