/*
	Written by Jtaim
	Mar 24 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Exercise 1
	A program that produces the sum of all the numbers in a file
	of whitespace-separated integers.
*/

#include "../includes/ppp.h"

int main()
try {
	const std::string FILE{ "ex1_data.txt" };

	std::ifstream fin{ FILE };
	int sum{}, data{};
	fin.exceptions(fin.exceptions() | std::ios::badbit);
	while (fin >> data) {
		sum += data;
	}
	if (fin.eof()) {
		fin.clear();
	}
	else if (fin.fail()) {
		ppp::error("bad input data found");
	}

	std::cout << "The sum of the integers from the " << FILE << " file is " << sum << ".\n";

	ppp::keep_window_open();
	return 0;
}
catch (std::exception& e) {
	std::cerr << R"(exception: )" << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << R"(exception)";
	ppp::keep_window_open();
	return 2;
}