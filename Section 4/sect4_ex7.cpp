//written by Jtaim
//date 3 Oct 2015
//update 17 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 7.
Modify the "mini calculator from exercise 5 to accept (just) single-digit numbers written as either digits
or spelled out.
*/

#include "section4.h"  // custom header
#include <vector>

void print_result(const int result);
bool get_number(int& num, const char term = '|');

int main()
{
	using std::cout;

	constexpr char TERM = '|';

	cout << "will loop to try more.  use '|' to exit.\n";
	bool exit = false;
	while (!exit)
	{
		cout << "Enter a number between 0 and 9.\n";
		cout << "Can either be spelled out or as a number followed by an operation (+, -, *, /)\n";
		int num1 = 0;
		int num2 = 0;
		char operation = '?';
		if (get_number(num1, TERM) && get_number(num2, TERM))
		{
			std::cin >> operation;
			switch (operation)
			{
			case '+':
				print_result(num1 + num2);
				break;
			case '-':
				print_result(num1 - num2);
				break;
			case '*':
				print_result(num1 * num2);
				break;
			case '/':
				if (num2 == 0)
				{
					simple_error("Division by zero.\n");
				}
				print_result(num1 / num2);
				break;
			case TERM:
				std::cout << "termination found\n";
				exit = true;
				break;
			default:
				simple_error("Wrong operation selected.\n");
			}
		}
		else
		{
			exit = true;
		}
		if (exit)
		{
			cout << "termination found.\n";
		}
	}
	keep_window_open();
	return 0;
}

// find number
bool get_number(int& num, const char term)
{
	const std::vector<std::string> NUMBERS{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	bool good = false;
	std::string str{ '?' };
	if (std::cin >> str)
	{
		// checking numbers
		if (isdigit(str.front()))
		{
			num = std::stoi(str);
			if (str.size() == 1)
			{
				good = true;
			}
			else
			{
				std::cout << "Was expecting single digit number.\n";
				good = true;	// letting < 1 valid number pass
			}
		}
		// check for termination
		else if (str.front() == term)
		{
			good = false;
		}
		else
			// check if number is spelled out
		{
			for (auto& i : str)
			{
				// cast to suppress conversion warning
				i = static_cast<char>(tolower(i));
			}
			// check if has a spelled out number
			auto num_index = NUMBERS.begin();
			for (; num_index != NUMBERS.end(); num_index++)
			{
				if (*num_index == str)
				{
					// cast to suppress conversion warning
					num = static_cast<int>(num_index - NUMBERS.begin());
					good = true;
					break;
				}
			}
			// check for termination
			if (num_index == NUMBERS.end())
			{
				auto i = str.begin();
				for (; i != str.end(); i++)
				{
					if (*i == term)
					{
						good = false;
						break;
					}
				}
				if (i == str.end())
				{
					simple_error("Input is junk\n");
				}
			}
		}
	}
	else
	{
		std::cin.clear();
		simple_error("cin error flag set\n");
	}
	return good;
}

// function to print result
void print_result(const int result)
{
	std::cout << "Your result is " << result << "\n\n";
}
