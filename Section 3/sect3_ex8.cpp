// written by Jtaim
//date 19 Sept 2015
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
    cout << "Enter an integer:" << endl;
    int val = 0;
    cin >> val;
    if(!cin) simple_error("something went bad with the read\n");
    string res = (val%2) ? "odd" : "even";   
    cout << "The value " << val << " is an " << res << " number\n";
	keep_window_open();
    return 0;
}