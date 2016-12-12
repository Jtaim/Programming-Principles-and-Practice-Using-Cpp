//written by Jtaim
//date 22 Sept 2015
//update 10 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 1. 
Write a program that consists of a while-loop that (each time around the loop) reads in 
two INTs and then prints them. Exit the program when a terminating '|' is entered.
*/

#include "section4.h"	//custom header
#include <vector>

typedef int num_type;

// return true if got valid numbers. 
// send reference for number and termination character
bool get_number(num_type& in_value, char term);

int main()
{
	using namespace std;
	const char TERMINATION_VALUE = '|';	//termination character
	const int HOW_MANY = 2;				//get 2 numbers per loop

	vector<num_type> values;
	num_type temp;
	bool more = true;
	while (more)
	{
		cout << "Enter two integer numbers. Enter " << TERMINATION_VALUE << " to exit.\n";
		int amount = 0;
		while ((amount < HOW_MANY) && more)
		{
			more = get_number(temp, TERMINATION_VALUE);
			if (more)
			{
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
			cout << "\n\n";
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