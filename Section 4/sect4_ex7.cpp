//written by Jtaim
//date 3 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 7.
Modify the "mini calculator from exercise 5 to accept (just) single-digit numbers written as either digits
or spelled out.
Write a program that performs as a very simple calculator.
Your calculator should be able to handle the four basic math operations — add, subtract, multiply, and divide — on two input values.
Your program should prompt the user to enter three arguments: two double values and a character to represent an operation.
If the entry arguments are 35.6, 24.1, and '+', the program output should be The sum of 35.6 and 24.1 is 59.7.
*/

#include "section4.h"  // custom header

void print_result(double);
bool check_input(int &inNum);

const vector<string> numbers{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int main()
{
	cout << "Enter 2 integer numbers between 0 and 9 and an operation (+, -, *, /): ";
	int num1 = 0;
	int num2 = 0;
	char operation = '?';
	while (check_input(num1) || check_input(num2)) {
		cout << "Invalid number selected.\n";
	}
	cin >> operation;
	switch (operation) {
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
	default:
		cout << "Wrong operation selected.\n";
	}
	keep_window_open();
	return 0;
}
// function to print result
void print_result(double result)
{
	cout << "Your result is " << result << endl;
}
// function to find correct number
bool check_input(int &inNum)
{
	cin >> inNum;
	bool good_num = false;
	if (cin.eof()) {  // EOF is captured
		cin.clear();
		//cin.ignore(INT_MAX, '\n');
		cout << "eof found\n";
		exit(1);  // exit program
	}
	else if (cin.fail()) { // invalid nonINT entry. check if correct spelled out
		cin.clear();  // clear cin error flags so can accept new data
		string sVal{ "??" };
		cin >> sVal;
		for (decltype(sVal.length()) i = 0; i < sVal.length(); ++i) { // set string to lower case
			sVal[i] = tolower(sVal[i]);
		}
		for (decltype(numbers.size()) i = 0; i < numbers.size(); ++i) {  // check if valid spelled out number
			if (sVal == numbers[i]) {
				inNum = i; // enter index as the number value
				good_num = false;
				break;  // match found break from for loop
			}
			else {
				good_num = true;
			}
		}
		if (good_num) {
			cin.ignore(INT_MAX, '\n');
		}
	}
	return good_num;
}