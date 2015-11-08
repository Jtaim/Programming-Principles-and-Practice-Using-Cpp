//written by Jtaim
//date 5 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 10
A program that reads and stores a series of doubles.
Ask user to enter number(N) of doubles want to sum.
Compute the sum of the first N doubles.
Create a vector of the first N doubles.
From that vector calculate the sum of those N doubles.
Also  provide a vector of the delta between delta[1] - delta[0], ..., delta[N] - delta[N-1].
Instruct user to terminate series with 'I' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

double sum_up(int, const vector<double> &);

int main()
try
{
	cout << "Enter how many numbers that you would like to sum:\n";
	int N = 0;
	/* while loop to get input and validate entry */
	while (true) {
		cin >> N;
		if (N < 0) {
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
	cout << "Enter some numbers (press '|' to stop):\n";
	vector<double> nums_entered;
	/* while loop to get doubles to place in a vector, validate and exit on an '|' entry */
	while (true) {
		double entered_num = 0;
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
	if (nums_entered.size() < static_cast<decltype(nums_entered.size())>(N)) { // cast to suppress warning
		error("not enough numbers entered to sum.\n");
	}
	vector<double> subnums_entered(nums_entered.begin(), nums_entered.begin()+N); // create new vector of N size
	double sum = sum_up(N, subnums_entered);  //summed numbers
	vector<double> deltas;
	for (unsigned i = 0; i < subnums_entered.size(); ++i) {
		if (i != 0) {
			deltas.push_back(subnums_entered[i] - subnums_entered[i - 1]);
		}
	}

	cout << "*********************************************************************\n";
	cout << "Selected number of numbers to sum:\t" << N << endl;
	cout << "Size of the number container:\t\t" << nums_entered.size() << '\n';
	cout << "Size of the sub number container:\t" << subnums_entered.size() << '\n';
	cout << "The sum of the selected numbers:\t" << sum << '\n';
	cout << "The deltas are:\t";
	for (auto x : deltas) {
		cout << x << ' ';
	}
	cout << '\n';
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
	keep_window_open();
	return 1;
}
catch (...) 
{
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
/*	Sums a vector to the user selected number to sum.
	Inputs:		int(N)
				reference to vector of doubles

	Outputs:	vector values summed to N input elements

	Errors:		number want to sum is larger than the vector size
*/
double sum_up(int x, const vector<double> &numbers)
{
	double sum = 0;
	//sum the numbers
	if (numbers.size() < static_cast<decltype(numbers.size())>(x)) { // cast to suppress warning
		error("not enough numbers entered to sum.\n");
	}
	for (int i = 0; i < x; i++) {
		sum += numbers[i];
	}
	return sum;
}