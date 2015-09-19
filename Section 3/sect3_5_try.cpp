//written by Jtaim
//date 18 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.5 try this exercise
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
//exit using EOF ctrl-z
int main()
{
	string previous = "";
	string current;
	while (cin >> current)
	{
		if(previous == current)
		{
			// what if word is repeated but one is capitalized?
			cout << "repeated word: " << current << endl;
		}
		previous = current;
	}
	return 0;
}