/*
	Written by Jtaim
	Mar 24 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Exercise 1
	A program that produces the sum of all the numbers in a file of whitespace-separated integers.
*/

#include "../includes/ppp.h"

int main()
try{
	constexpr char file_name[]{"sect10_ex1.txt"};

	std::ifstream fin{file_name};
	int sum{};
	fin.exceptions(fin.exceptions() | std::ios::badbit);
	for(int n{}; fin >> n; sum += n){/*all done in for loop declaration*/}
	if(fin.fail() && !fin.eof()){
		ppp::error("bad input data found");
	}
	std::cout << "The sum of the integers from the " << file_name << " file is " << sum << ".\n";

	ppp::keep_window_open();
	return 0;
}
catch(std::exception& e){
	std::cerr << R"(exception: )" << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << R"(exception)";
	ppp::keep_window_open();
	return 2;
}