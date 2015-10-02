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

void print_result(double);

int main()
{
	cout << "Enter 2 numbers and an operation (+, -, *, /): ";
	double num1 = 0;
	double num2 = 0;
	char operation = '?';
	cin >> num1 >> num2 >> operation;
	switch(operation) {
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
			if (!num2) {
				cout << "Division by zero.\n";
			}
			print_result(num1 / num2);
			break;
		default: {
			if (cin.eof()) {  // EOF is captured
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "eof found\n";
			}
			else if(cin.fail()) {  // bad input is captured
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid input found\n";
			}
			else {
				cout << "Wrong operation selected.\n";
			}
		}
	}
    keep_window_open();
	return 0;
}
void print_result(double result)
{
	cout << "Your result is " << result << endl;
}