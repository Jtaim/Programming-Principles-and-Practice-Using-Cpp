//written by James Weiland
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 5. 
Write a program that performs as a very simple calculator. 
Your calculator should be able to handle the four basic math operations — add, subtract, multiply, and divide — on two input values. 
Your program should prompt the user to enter three arguments: two double values and a character to represent an operation. 
If the entry arguments are 35.6, 24.1, and '+', the program output should be The sum of 35.6 and 24.1 is 59.7. 
*/

#include "std_lib_facilities.h" 							// custom header

int main()
try
{
	cout << "Enter 2 numbers and an operation (+, -, *, /): ";
	double num1 = 0;
	double num2 = 0;
	char operation = '?';
	double result = 0;
	cin >> num1 >> num2 >> operation;
	switch(operation) {
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			if (!num2) {
				error("Division by zero.");
			}
			result = num1 / num2;
			break;
		default:
			error("Wrong operation selected");
	}
	cout << "Your result is " <<  num1 << " " << operation << " " << num2 << " = " << result << endl;
	return 0;
}
catch (runtime_error e) {
	// this code is to produce error messages; it will be described in Chapter 5
	cout << e.what() << endl;
}
catch (...) {
	// this code is to produce error messages; it will be described in Chapter 5
	cout << "exiting\n";
}