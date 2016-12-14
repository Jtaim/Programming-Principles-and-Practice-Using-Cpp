//written by Jtaim
//date 19 Sept 2015
//updated 2 Dec 2016
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
	int penny = 0;
	int nickel = 0;
	int dime = 0;
	int quarter = 0;
	int half_dollar = 0;
	int dollar = 0;
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

	string denomination = "???";
	if (penny == 1) { denomination = "penny"; }
	else { denomination = "pennies"; }
	if (penny > 0) { cout << "you have " << penny << " " << denomination << endl; }
	if (nickel == 1) { denomination = "nickel"; }
	else { denomination = "nickels"; }
	if (nickel > 0) { cout << "you have " << nickel << " " << denomination << endl; }
	if (dime == 1) { denomination = "dime"; }
	else { denomination = "dimes"; }
	if (dime > 0) { cout << "you have " << dime << " " << denomination << endl; }
	if (quarter == 1) { denomination = "quarter"; }
	else { denomination = "quarters"; }
	if (quarter > 0) { cout << "you have " << quarter << " " << denomination << endl; }
	if (half_dollar == 1) { denomination = "half dollar"; }
	else { denomination = "half dollars"; }
	if (half_dollar > 0) { cout << "you have " << half_dollar << " " << denomination << endl; }
	if (dollar == 1) { denomination = "dollar"; }
	else { denomination = "dollars"; }
	if (dollar > 0) { cout << "you have " << dollar << " " << denomination << endl; }

	double total;
	total = penny + nickel * 5 + dime * 10 + quarter * 25 + half_dollar * 50 + dollar * 100;
	total /= 100;
	cout << "your total is $" << total << endl;
	keep_window_open();
	return 0;
}
