//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 5.
Write a program that performs as a very simple calculator.
Your calculator should be able to handle the four basic math operations — add, subtract, multiply, and divide — on two input values.
Your program should prompt the user to enter three arguments: two double values and a character to represent an operation.
If the entry arguments are 35.6, 24.1, and '+', the program output should be The sum of 35.6 and 24.1 is 59.7.
*/

#include "section4.h"
#include <unordered_map>

double add(double arg1, double arg2)
{
	return arg1 + arg2;
}

double subtract(double arg1, double arg2)
{
	return arg1 - arg2;
}

double multiply(double arg1, double arg2)
{
	return arg1 * arg2;
}

double divide(double arg1, double arg2)
{
	if(arg2 == 0){
		simple_error("division by zero is not allowed.\n");
	}
	return arg1 / arg2;
}

using math = double(*)(double, double);
std::unordered_map<char, math> calculate{
	{'+', add},
	{'-', subtract},
	{'*', multiply},
	{'/', divide}
};

int main()
{
	std::cout << "Enter 2 numbers and an operation (+, -, *, /).\n";
	double arg1{}, arg2{};
	if(!(std::cin >> arg1 >> arg2)){
		simple_error("incorrect numbers entered.\n");
	}

	char op{};
	std::cin >> op;
	auto itr{calculate.find(op)};
	if(itr == calculate.end()){
		simple_error("incorrect operator entered.\n");
	}
	std::cout << arg1 << " " << op << " " << arg2 << " = " << itr->second(arg1, arg2) << std::endl;

	keep_window_open();
	return 0;
}
