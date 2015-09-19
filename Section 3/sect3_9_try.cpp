//written by Jtaim
//date 18 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.9 try this exercise
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
//exit EOF ctrl-z
int main()
{
	double d = 0;
    while (cin>>d)	            		
	{
        int i = d;						// try to squeeze a double into an int
		//int i {d};						// the {} enforce error narrowing error
		char c = i;            			// try to squeeze an int into a char
		int i2 = c;             		// get the integer value of the character
        cout << "d==" << d      		// the original double
             << " i=="<< i      		// converted to int
             << " i2==" << i2   		// int value of char
             << " char(" << c << ")\n"; // the char
    }
	return 0;
}