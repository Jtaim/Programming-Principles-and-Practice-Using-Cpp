//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3 exercise 10.
a program that takes an operation followed by two operands and outputs the result. For example:
+ 100 3.14
* 4 5
Read the operation into a string called operation and use an if-statement to figure out which
operation the user wants, for example, if (operation=="+"). Read the operands into variables
of type double. Implement this for operations called +, –, *, /, add, subtract, multiply, and divide
with their obvious meanings.
*/

#include "section3.h"

int main()
{
	using namespace std;

	const vector<string> op{"+", "-", "*", "/", "add", "subtract", "multiply", "divide"};
	cout << "Enter an operation (+, -, *, /, add, subtract, multiply, and divide) followed by 2 operands separated by spaces:\n";

	string operation;
	// check for good operation
	bool goodOperation{false};
	cin >> operation;
	if(std::find(op.cbegin(), op.cend(), operation) == op.cend()){
		simple_error("Bad Operator");
	}

	double val1{};
	double val2{};
	// check for good operands
	if(!(cin >> val1 >> val2)){
		simple_error("Bad Operands");
	}

	double result{};
	// compute result
	if(operation == "+" || operation == "add"){
		result = val1 + val2;
		operation = "+";
	} else if(operation == "-" || operation == "subtract"){
		result = val1 - val2;
		operation = "-";
	} else if(operation == "*" || operation == "multiply"){
		result = val1 * val2;
		operation = "*";
	} else if(operation == "/" || operation == "divide"){
		if(val2 == 0){
			simple_error("divide by zero");
		}
		result = val1 / val2;
		operation = "/";
	} else{
		simple_error("Unknown operator!");
	}

	// print results
	cout << val1 << " " << operation << " " << val2 << " = " << result << endl;

	keep_window_open();
	return 0;
}
