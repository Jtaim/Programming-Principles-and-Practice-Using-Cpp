//written by Jtaim
//date 19 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3 exercise 2.
converts from miles to kilometers (1.609 kilometers to the mile)
*/

#include "section3.h" //custom header

//C++ programs start by executing the function main
int main()
{
    cout << "Enter the number of miles you want to convert to kilometers:" << endl;
    double miles;
    cin >> miles;
    cout << miles << " miles converted to kilometers is " << miles * 1.609 << endl;
	keep_window_open();
    return 0;
}