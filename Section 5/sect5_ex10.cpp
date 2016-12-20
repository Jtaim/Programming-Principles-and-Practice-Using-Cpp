//written by Jtaim
//date 5 Nov 2015
//updated 19 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 10
A program that reads and stores a series of doubles.
Ask user to enter number(N) of doubles want to sum.
Compute the sum of the first N doubles.
Create a vector of the first N doubles.
From that vector calculate the sum of those N doubles.
Also  provide a vector of the delta between delta[1] - delta[0], ..., delta[N] - delta[N-1].
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

double sum_up(int, const std::vector<double> &);

int main()
try
{
	using std::cout;
	using std::cin;
	using std::endl;

	constexpr char TERMINATION = '|';

	cout << "Enter how many integers that you would like to sum (press '|' to stop)\n";
	int num_sum = 0;
	std::vector<int> nums_entered;
	/* while loop to get input and validate entry */
	bool exit = false;
	while (!exit)
	{
		cin >> num_sum;
		if (!cin.good())
		{
			cin.clear();
			char c;
			cin.get(c);
			cin.ignore(INT8_MAX, '\n');
			if (c == TERMINATION)
			{
				exit = true;
			}
			else
			{
				cout << "Invalid entry!\n";
			}
		}
		else if (num_sum <= 0)
		{
			cout << "Invalid entry!\n";
		}
		else
		{
			break; //found valid number
		}
	}
	if (!exit)
	{
		cout << "Enter some integers (press '|' to stop)\n";
		/* while loop to get integers to place in a vector, validate and exit on an '|' entry */
		int entered_num = 0;
		while (!exit)
		{
			// loads entered numbers into a container vector
			if (cin >> entered_num)
			{
				nums_entered.push_back(entered_num);
			}
			else
			{
				cin.clear();
				char c;
				cin.get(c);
				cin.ignore(INT8_MAX, '\n');
				if (c == TERMINATION)
				{
					exit = true;
				}
				else
				{
					cout << "Invalid entry!\n";
				}
			}
		}
	}
	if (nums_entered.size() < num_sum)
	{
		error("not enough numbers entered to sum.\n");
	}
	std::vector<double> subnums_entered(nums_entered.begin(), nums_entered.begin() + num_sum);
	double sum = sum_up(num_sum, subnums_entered);	//summed numbers
	std::vector<double> deltas;
	for (unsigned i = 0; i < subnums_entered.size(); ++i)
	{
		if (i != 0)
		{
			deltas.push_back(subnums_entered[i] - subnums_entered[i - 1]);
		}
	}

	cout << "*********************************************************************\n";
	cout << "Selected number of numbers to sum:\t" << num_sum << endl;
	cout << "Size of the number container:\t\t" << nums_entered.size() << '\n';
	cout << "Size of the sub number container:\t" << subnums_entered.size() << '\n';
	cout << "The sum of the selected numbers:\t" << sum << '\n';
	cout << "The deltas are:\t";
	for (auto x : deltas)
	{
		cout << x << ' ';
	}
	cout << '\n';
	cout << "*********************************************************************\n";
	/* for to print all valid entries */
	for (auto x : nums_entered)
	{
		cout << x << '\n';
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

/*	Sums a vector to the user selected number to sum.
	Inputs:		int(N)
				reference to vector of doubles

	Outputs:	vector values summed to N input elements

	Errors:		number want to sum is larger than the vector size
*/
double sum_up(int x, const std::vector<double> &numbers)
{
	double sum = 0;
	//sum the numbers
	if (numbers.size() < x)
	{
		error("not enough numbers entered to sum.\n");
	}
	for (int i = 0; i < x; i++)
	{
		sum += numbers[i];
	}
	return sum;
}
