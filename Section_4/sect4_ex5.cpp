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

#include "section4.h"  // custom header

bool get_numbers(std::pair<double,double>&);
bool check_term(const char);
void print_result(const double);

int main()
{
	using namespace std;

	constexpr auto termination = '|';
	const vector<char> ops{ '+','-','*','/' };

	pair<double, double> numbers{ 0.0, 0.0 };
	auto exit{ false };
	while (!exit) {
		cout << "Enter 2 numbers and an operation (+, -, *, /). Use " << termination << " to exit.\n";
		while (!get_numbers(numbers)) {
			exit = check_term(termination);
			if (exit == false) {
				cout << "a bad number was entered. please re-enter numbers or exit\n";
			}
			else { break; }
		}
		if (exit == false) {
			char op;
			cin >> op;
			if (find(ops.begin(), ops.end(), op) != ops.end()) {
				switch (op) {
				case '+': print_result(numbers.first + numbers.second);
					break;
				case '-': print_result(numbers.first - numbers.second);
					break;
				case '*': print_result(numbers.first * numbers.second);
					break;
				case '/':
					if (numbers.second != 0) {
						print_result(numbers.first / numbers.second);
					}
					else {
						simple_error("division by zero is not allowed.\n");
					}
					break;
				default:
					simple_error("should not be here.\n");
				}
			}
			else {
				cin.putback(op);
				exit = check_term(termination);
				if (exit == false) {
					cout << "bad operation entered. please re-enter equation or exit\n";
				}
			}
		}
	}
	cout << "Bye\n";
	keep_window_open();
	return 0;
}

bool get_numbers(std::pair<double, double>& pd)
{
	if (!(std::cin >> pd.first)) {
		return false;
	}
	if (!(std::cin >> pd.second)) {
		return false;
	}
	return true;
}

bool check_term(const char t)
{
	if (std::cin.eof() || std::cin.bad())
	{
		return true;
	}
	std::cin.clear();
	std::string str;
	std::cin >> str;
	if (str.find(t) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}

void print_result(const double result)
{
	std::cout << "Your result is " << result << std::endl;
}
