/*
	Written by Jtaim
	Date 21 Dec 2018
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup
	Section 8 Exercise 2
	Write a function print() that prints a vector of ints to cout.
	Inputs: string for labeling
			vector
	Outputs: void
*/

#include "..\includes\ppp.h"

#include<iostream>
#include<string>
#include<vector>

void print(const std::string& label, const std::vector<int>& v)
{
	std::cout << label << '\n';
	for(auto i : v){
		std::cout << i << '\n';
	}
}

int main()
{
	std::string label{"Printing some integers from a vector."};
	std::vector<int> vi{1, 2, 3, 4, 5};
	print(label, vi);

	ppp::keep_window_open();
	return 0;
}