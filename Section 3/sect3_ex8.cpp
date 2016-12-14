// written by Jtaim
//date 19 Sept 2015
//updated 2 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3 exercise 8.
A program to test an integer value to determine if it is odd or even. 
As always, make sure your output is clear and complete. 
In other words, don’t just output yes or no. Your output should stand alone, 
like The value 4 is an even number. Hint: See the remainder (modulo) operator in §3.4.
*/

#include "section3.h" //custom header

//C++ programs start by executing the function main
int main()
{
	std::cout << "Enter an integer: ";
	int val = 0;
	std::cin >> val;
	if (!std::cin) simple_error("Error entered a none integer value\n");
	std::string res = (val % 2) ? "odd" : "even";
	std::cout << "The value " << val << " is a " << res << " number\n";
	keep_window_open();
	return 0;
}
