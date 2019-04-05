/*
	Written by Jtaim
	Feb 26 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Drill 1
	Test program Point class.
*/

#include "../includes/ppp.h"
#include "Point.h"

int main()
try {
	Point<int> a;
	Point b{ 2,3 };

	std::cout << a << "\n";
	std::cout << b << "\n";

	if (!(std::cin >> a) && !std::cin.eof()) {
		std::cout << "bad input\n";
	}
	else {
		std::cout << a << "\n";
	}

	ppp::keep_window_open();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "exception\n";
	ppp::keep_window_open();
	return 2;
}