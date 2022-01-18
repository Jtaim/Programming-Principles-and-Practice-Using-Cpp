/*
	Written by Jtaim
	Sept 4 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 16
	this is the test program Money class.
*/

#include"../includes/ppp.h"

#include "Money.h"

int main()
try{
	std::cout << "Enter a monitory amount prefixed by currency code (USD or DKK)\n";
	Money m1, m2;
	std::cin >> m1 >> m2;
	std::cout << "m1 = " << m1 << '\n';
	std::cout << "m2 = " << m2 << '\n';

	std::cout << "m1 + m2 = " << m1 + m2 << "\n";

	ppp::keep_window_open();
	return 0;
}
catch(std::exception& e){
	std::cerr << "exception: " << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "exception\n";
	ppp::keep_window_open();
	return 2;
}