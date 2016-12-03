// written by Jtaim
//date 19 Sept 2015
//updated 2 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3 exercise 4.
A program that prompts the user to enter two integer values. 
Store these values in int variables named val1 and val2. 
Section 3 exercise 5
repeat for double values
Write your program to determine the smaller, larger, sum, difference, 
product, and ratio of these values and report them to the user.
*/

#include "section3.h" //custom header

//C++ programs start by executing the function main
int main()
{
	using std::cout;
	using std::cin;
	using std::endl;
	//cout << "Enter two integer values:\n";
    cout << "Enter two float values:\n";
    //int val1, val2;
    double val1, val2;
    cin >> val1 >> val2;
    if(val1<val2)
        cout << val1 << " is smaller than " << val2 << endl;
    if(val1>val2)
        cout << val2 << " is smaller than " << val1 << endl;
    if(val1==val2)
        cout << val1 << " is equal to " << val2 << endl;
        
    cout << "The sum of " << val1 << " and " << val2 << " is " << val1+val2 << endl;
    cout << "The difference of " << val1 << " and " << val2 << " is " << val1-val2 << endl;
    cout << "The product of " << val1 << " and " << val2 << " is " << val1*val2 << endl;
    if (val2==0)
		simple_error("good try! but I don't divide by zero\n");
	else
        cout << "The ration of " << val1 << " and " << val2 << " is " << val1/val2 << endl;
	keep_window_open();
	return 0;
}