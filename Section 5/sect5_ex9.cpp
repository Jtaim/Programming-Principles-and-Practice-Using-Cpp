//written by Jtaim
//date 4 Nov 2015
//updated 19 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 9
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Compute the sum of the first N integers.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector

Added overflow error when summing
*/

#include "section5.h"

int sum_up(int nums_to_sum, const std::vector<int> &vector_of_numbers);

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
	int sum = sum_up(num_sum, nums_entered);	//summed numbers

	cout << "*********************************************************************\n";
	cout << "Selected number of integers to sum: \t" << num_sum << endl;
	cout << "Size of the integer container: \t\t" << nums_entered.size() << '\n';
	cout << "The sum of the selected integers: \t" << sum << '\n';
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
	Inputs:		int
				reference to vector of integers

	Outputs:	vector values summed to input int elements

	Errors:		number want to sum is larger than the vector size
				if the sum of the element cause and int type overflow
*/
int sum_up(int nums_to_sum, const std::vector<int> &vector_of_numbers)
{
	int sum = 0;
	if (vector_of_numbers.size() < nums_to_sum)
	{
		error("not enough integers entered to sum.\n");
	}
	else
	{	//sum the numbers
		for (int i = 0; i < nums_to_sum; i++)
		{
			if ((vector_of_numbers[i] > 0) && (sum > INT_MAX - vector_of_numbers[i]))
			{
				error("int overflow error");
			}
			if ((vector_of_numbers[i] < 0) && (sum < INT_MAX - vector_of_numbers[i]))
			{
				error("int overflow error");
			}
			sum += vector_of_numbers[i];
		}
	}
	return sum;
}
