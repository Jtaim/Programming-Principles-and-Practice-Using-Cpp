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

#include "section3.h"

int getInput()
{
	int val{};
	if(!(std::cin >> val)){
		simple_error("Invalid integer value\n");
	}
	return val;
}

int main()
{
	using namespace std;

	cout << "Lets count some change $$$$!\n";
	int penny{};
	int nickel{};
	int dime{};
	int quarter{};
	int half_dollar{};
	int dollar{};
	cout << "Enter number of pennies: ";
	penny = getInput();
	cout << "Enter number of nickels: ";
	nickel = getInput();
	cout << "Enter number of dimes: ";
	dime = getInput();
	cout << "Enter number of quarters: ";
	quarter = getInput();
	cout << "Enter number of half dollars: ";
	half_dollar = getInput();
	cout << "Enter number of dollar coins: ";
	dollar = getInput();

	string denomination;
	if(penny > 0){
		denomination = (penny == 1 ? "penny" : "pennies");
		cout << "you have " << penny << " " << denomination << endl;
	}

	if(nickel > 0){
		denomination = (nickel == 1 ? "nickel" : "nickels");
		cout << "you have " << nickel << " " << denomination << endl;
	}

	if(dime > 0){
		denomination = (dime == 1 ? "dime" : "dimes");
		cout << "you have " << dime << " " << denomination << endl;
	}

	if(quarter > 0){
		denomination = (quarter == 1 ? "quarter" : "quarters");
		cout << "you have " << quarter << " " << denomination << endl;
	}

	if(half_dollar > 0){
		denomination = (half_dollar == 1 ? "half dollar" : "half dollars");
		cout << "you have " << half_dollar << " " << denomination << endl;
	}

	if(dollar > 0){
		denomination = (dollar == 1 ? "dollar" : "dollars");
		cout << "you have " << dollar << " " << denomination << endl;
	}

	long long total{};
	total = penny + nickel * 5LL + dime * 10LL + quarter * 25LL + half_dollar * 50LL + dollar * 100LL;
	cout << "your total is $" << fixed << total / 100.0L << endl;

	keep_window_open();
	return 0;
}
