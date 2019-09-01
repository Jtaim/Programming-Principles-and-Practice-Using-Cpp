//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 7.
Modify the "mini calculator from exercise 5 to accept (just) single-digit numbers written as either digits
or spelled out.
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

bool getNumber(double& arg, const std::vector<std::string>& spelledNumbers)
{
	if(std::cin >> arg){
		return true;
	}
	// check if number is spelled out
	std::cin.clear();
	std::string spelledNumber;
	std::cin >> spelledNumber;
	// convert to lower
	std::transform(spelledNumber.begin(), spelledNumber.end(), spelledNumber.begin(), [](char c){
		return static_cast<char>(tolower(c));
	});
	// check if has a spelled out number
	auto spelledIndex = std::find(spelledNumbers.begin(), spelledNumbers.end(), spelledNumber);
	if(spelledIndex == spelledNumbers.end()){
		return false;
	}
	arg = static_cast<int>(spelledIndex - spelledNumbers.begin());
	return true;
}

using math = double(*)(double, double);
std::unordered_map<char, math> calculate{
	{'+', add},
	{'-', subtract},
	{'*', multiply},
	{'/', divide}
};

const std::vector<std::string> spelledNumbers{
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int main()
{
	std::cout << "Enter 2 numbers and an operation (+, -, *, /).\n";
	std::cout << "Number entered must be between 0 and 9 either spelled out or as the number.\n\n";

	double arg1{}, arg2{};
	if(!getNumber(arg1, spelledNumbers) || !getNumber(arg2, spelledNumbers)){
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
