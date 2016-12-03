//written by Jtaim
//date 17 Sept 2015
//updated 1 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.4 try this exercise
*/

#include <iostream>
#include <string>
#include <cmath>		//for sqrt function
#include "section3.h"	//custom header

//C++ programs start by executing the function main
int main()
{
	using namespace std;
	cout << "Please enter a value: ";
	int n;
	cin >> n;
	cout << "n == " << n << endl
		 << "n+1 == " << n+1 << endl
		 << "three times n == " << 3*n << endl
		 << "twice n == " << n+n << endl
		 << "n squared == " << n*n<< endl
		 << "half of n == " << static_cast<double>(n)/2 << endl
		 << "square root of n == " << static_cast<double>(sqrt(n)) << endl;

	keep_window_open();
	return 0;
}