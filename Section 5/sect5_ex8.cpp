//written by Jtaim
//date 2 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 8
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Compute the sum of the first N integers.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with 'I' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

int main()
try 
{
	cout << "Enter how many integers that you would like to sum: " << endl;
	int num_sum = 0;
	/* while loop to get input and validate entry */
	while(true) {
		cin >> num_sum;
		if (num_sum < 0) {
			cout << "Number to sum must be >= 0.\n";
		}
		else if (cin.fail()) {
			cin.clear();
			cin.ignore(INT8_MAX, '\n');
			cout << "Invalid entry!\n";
		}
		else {
			break; //found valid number
		}
	}
	cout << "Enter some integers (press '|' to stop): " << endl;
	vector<int> nums_entered;
	/* while loop to get integers to place in a vector, validate and exit on an '|' entry */
	while (true) {
		int entered_num = 0;
		if (cin >> entered_num) {
			nums_entered.push_back(entered_num); // loads entered numbers into a container vector
		}
		else {
			cin.clear(); // clear cin error
			char termination;
			cin >> termination; // get termination char
			if (termination == '|') {
				break;  // found valid termination
			}
			else {
				cout << termination << " is an invalid entry\n";
			}
		}
	}
	int sum = 0;  //summed numbers
	/* if vector not large enough to sum N numbers error, else sum N numbers */
	if (nums_entered.size() < static_cast<decltype(nums_entered.size())>(num_sum)) { // cast to suppress warning
		error("not enough integers entered to sum.\n");
	}
	else { //sum the numbers
		for (int i = 0; i < num_sum; i++)
		{
			sum += nums_entered[i];
		}
	}
	cout << "*********************************************************************\n";
	cout << "Selected number of integers to sum: \t" << num_sum << endl;
	cout << "Size of the integer container: \t\t" << nums_entered.size() << '\n';
	cout << "The sum of the selected integers: \t" << sum << '\n';
	cout << "*********************************************************************\n";
	/* for to print all valid entries */
	for (auto x : nums_entered) {
		cout << x << '\n';
	}
	keep_window_open();
	return 0;
}
catch (exception& e) 
{
	cerr << "error: " << e.what() << '\n';
//	keep_window_open();
	return 1;
}
catch (...) 
{
	cerr << "Oops: unknown exception!\n";
//	keep_window_open();
	return 2;
}