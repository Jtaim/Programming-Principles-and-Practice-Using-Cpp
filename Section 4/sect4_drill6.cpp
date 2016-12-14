//written by Jtaim
//date 25 Sept 2015
//updated 10 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 6.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if they are equal.
4. Change the program so that it uses double instead of int.
5. Change the program so that it writes out the numbers are almost equal after writing
   out which is the larger and the smaller if the two numbers differ by less than 1.0 / 100.
6. Now change the body of the loop so that it reads just one double each time around.
   Define two variables to keep track of which is the smallest and which is the largest
   value you have seen so far. Each time through the loop write out the value entered.
   If it’s the smallest so far, write the smallest so far after the number.
   If it is the largest so far, write the largest so far after the number.
*/

#include "section4.h"		//custom header
#include <vector>

typedef double num_type;	// set type to work with

// return true if got valid numbers. 
// send reference for number and termination character
bool get_number(num_type& in_value, char term);

int main()
{
	using namespace std;
	const char TERMINATION_VALUE = '|';	// termination character

	vector<num_type> values;			// vector to hold valid input numbers
	num_type temp;						// temp memory for input numbers
	bool more = true;					// false when term character is entered

	num_type small_num;
	num_type large_num;
	while (more)	// get numbers
	{
		cout << "Enter two numbers. Enter " << TERMINATION_VALUE << " to exit.\n";
		more = get_number(temp, TERMINATION_VALUE);
		if (more)
		{
			cout << "The currently entered number: " << temp << endl;
			if (values.size() == 0)
			{
				cout << temp << " is now the smallest number.\n";
				cout << temp << " is now the largest number.\n";
				small_num = large_num = temp;
			}
			else if (temp < small_num)
			{
				cout << temp << " is now the smallest number.\n";
				small_num = temp;
			}
			else if (temp > large_num)
			{
				cout << temp << " is now the largest number.\n";
				large_num = temp;
			}
			values.push_back(temp);
		}
	}
	if (values.size() != 0)
	{
		cout << "The numbers entered: ";
		for (auto i : values)
		{
			cout << i << " ";
		}
		cout << "\n";
		cout << "The largest number:  " << large_num << endl;
		cout << "The smaller number:  " << small_num << "\n\n";
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
