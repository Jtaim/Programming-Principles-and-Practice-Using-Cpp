/*
	Written by Jtaim
	Date 22 Dec 2018
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 8 Exercise 5
	Write 2 functions that reverse the element order in a vector<int>.
	One function should produce a new vector with the elements reversed, not affecting the original vector.
	The other should reverse the elements with out using a new vector.
*/

#include "..\includes\ppp.h"

#include<iostream>
#include<vector>

using vect_values = std::vector<int>;

void reverse(const vect_values& v, vect_values& rv)
{
	rv.clear();
	if(!v.empty()){
		for(auto iv{v.crbegin()}; iv != v.crend(); ++iv){
			rv.push_back(*iv);
		}
	}
}

void reverse(vect_values& v)
{
	if(!v.empty()){
		auto rv{v};
		rv.clear();
		for(auto iv{v.crbegin()}; iv != v.crend(); ++iv){
			rv.push_back(*iv);
		}
		v.swap(rv);
	}
}

int main()
{
	vect_values a{0,1,2,3,4,5};
	vect_values b;

	reverse(a, b);
	for(auto n : b){
		std::cout << n << ' ';
	}
	std::cout << std::endl;

	reverse(b);
	for(auto n : b){
		std::cout << n << ' ';
	}
	std::cout << std::endl;

	ppp::keep_window_open();
	return 0;
}