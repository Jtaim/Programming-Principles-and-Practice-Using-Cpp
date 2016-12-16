//written by Jtaim
//date 1 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 5. 
Write a program that performs as a very simple calculator. 
Your calculator should be able to handle the four basic math operations — add, subtract, multiply, and divide — on two input values. 
Your program should prompt the user to enter three arguments: two double values and a character to represent an operation. 
If the entry arguments are 35.6, 24.1, and '+', the program output should be The sum of 35.6 and 24.1 is 59.7. 
*/

#include "section4.h"  // custom header

bool get_number(double& num);
void print_result(double);

int main()
{
	using std::cout;
	using std::cin;

	constexpr char TERMINATION = '|';

	double num1{ 0 };
	double num2{ 0 };
	char operation{ '?' };
	bool exit = false;
	while (!exit)
	{
		cout << "Enter 2 numbers and an operation (+, -, *, /). Use " << TERMINATION << " to exit.\n";
		if (get_number(num1) && get_number(num2))
		{
			cin >> operation;
			switch (operation)
			{
			case '+': print_result(num1 + num2);
				break;
			case '-': print_result(num1 - num2);
				break;
			case '*': print_result(num1 * num2);
				break;
			case '/':
				if (num2 != 0)
				{
					print_result(num1 / num2);
				}
				else
				{
					simple_error("division by zero is not allowed.\n");
				}
				break;
			case TERMINATION :
				exit = true;
				break;
			default:
				cout << "Wrong operator selected.\n";
			}
		}
		else
		{
			// EOF is captured
			if (cin.eof())
			{
				exit = true;
				cout << "EOF found\n";
			}
			cin.clear();
			char c;
			cin >> c;
			if (c == TERMINATION)
			{
				exit = true;
				cout << "termination found\n";
			}
			cin.ignore(32768, '\n');
		}
	}
	keep_window_open();
	return 0;
}

bool get_number(double & num)
{
	if (std::cin >> num)
		return true;
	else
	{
		std::cout << "Incorrect number entry\n";
		return false;
	}
}

void print_result(double result)
{
	std::cout << "Your result is " << result << std::endl;
}