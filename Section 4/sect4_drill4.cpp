//written by Jtaim
//date 24 Sept 2015
//updated 10 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 4.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if they are equal.
4. Change the program so that it uses double instead of int.
*/

#include "section4.h"	//custom header
#include <vector>

typedef double num_type;	// set type to work with

// return true if got valid numbers. 
// send reference for number and termination character
bool get_number(num_type& in_value, char term);

int main()
{
	using namespace std;
	const char TERMINATION_VALUE = '|';	// termination character
	const int HOW_MANY = 2;				// get 2 numbers per loop

	vector<num_type> values;			// vector to hold valid input numbers
	num_type temp;						// temp memory for input numbers
	bool more = true;					// false when term character is entered
	while (more)
	{
		num_type small_num;
		num_type large_num;
		cout << "Enter two integer numbers. Enter " << TERMINATION_VALUE << " to exit.\n";
		int amount = 0;
		while ((amount < HOW_MANY) && more)	// get numbers
		{
			more = get_number(temp, TERMINATION_VALUE);
			if (more)
			{
				if (amount == 0)
					small_num = large_num = temp;
				else if (temp < small_num)
					small_num = temp;
				else if (temp > large_num)
					large_num = temp;
				values.push_back(temp);
				amount++;
			}
		}
		if (more)
		{
			cout << "The numbers entered: ";
			for (auto i : values)
			{
				cout << i << " ";
			}
			cout << "\n";
			// assuming only 2 entries total
			if (values.front() == values.back())
			{
				cout << "The values entered are equal.\n\n";
			}
			else
			{
				cout << "The largest number:  " << large_num << endl;
				cout << "The smaller number:  " << small_num << "\n\n";
			}
		}
		values.clear();
	}
	cout << "bye\n";
	keep_window_open();
	return 0;
}

bool get_number(num_type& in_value, char term)
{
	while (1)
	{
		if (!(std::cin >> in_value))
		{
			std::cin.clear();
			char termination;
			std::cin >> termination;
			if (termination == term)
			{
				std::cout << "Program terminated\n";
				return false;
			}
			else
			{
				std::cout << "Entered an incorrect value try again:\n";
				std::cin.ignore(32765, '\n');
			}
		}
		else
		{
			return true;
		}
	}
}
