//written by Jtaim
//date 1 Oct 2015
//updated 15 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 6. 
Make a vector holding the ten string values "zero", "one", . . . "nine". 
Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output seven. 
Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input seven gives the output 7.
*/

#include "section4.h"
#include <vector>


int main()
{
	using std::cout;
	using std::cin;

	const std::vector<std::string> NUMBERS{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	constexpr char TERMINATION = '|';

	cout << "will loop to try more.  use '|' to exit.\n";
	int number{ -1 };
	bool exit = false;
	while (!exit)
	{
		cout << "Enter a number between 0 and 9 either spelled out or as the number.\n";
		std::string str{ '?' };
		if (cin >> str)
		{
			// checking for only 1 digit numbers
			if (str.size() == 1)
			{
				// check is a number
				if (isdigit(str.front()))
				{
					number = std::stoi(str);
				}
				// check for termination
				else if (str.front() == TERMINATION)
				{
					exit = true;
				}
				else
				{
					simple_error("Input is junk\n");
				}
			}
			// check if number is spelled out
			else if (str.size() > 1)
			{
				for (auto& i : str)
				{
					i = tolower(i);
				}
				// check if has a spelled out number
				bool found = false;
				for (auto num_index = NUMBERS.begin(); num_index != NUMBERS.end(); num_index++)
				{
					if (*num_index == str)
					{
						number = static_cast<int>(num_index - NUMBERS.begin());
						found = true;
						break;
					}
				}
				// check for termination
				if (!found)
				{
					for (auto i = str.begin(); i != str.end(); i++)
					{
						if (*i == TERMINATION)
						{
							exit = true;
							break;
						}
					}
				}
				if (!found && !exit)
				{
					simple_error("Input is junk\n");
				}
			}
			else
			{
				simple_error("Not sure how got here\n");
				exit = true;
			}
		}
		else
		{
			cout << "cin error flag set\n";
			cin.clear();
			exit = true;
		}
		if (!exit)
		{
			cout << "The number entered is " << number << "\n\n";
		}
	}
	cout << "bye\n";
	keep_window_open();
	return 0;
}
