//written by Jtaim
//date 17 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.4 try this exercise
*/

//#include "std_lib_facilities.h" //custom header
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;
inline void keep_window_open() { char ch; cin >> ch; }

//C++ programs start by executing the function main
int main()
{
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