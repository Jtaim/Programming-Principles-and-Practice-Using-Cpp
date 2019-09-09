/*
	Written by Jtaim
	Sept 8 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Exercise 11
	Write a program that produces the sum of all the whitespace-separated integers in a text file.
	For example, bears: 17 elephants 9 end should output 26.
*/

#include "../includes/ppp.h"

constexpr std::string_view txt_file{"sect10_ex11.txt"};

int main()
try{
	std::ifstream fin{txt_file.data()};
	if(!fin){
		ppp::error("could not open ", txt_file.data());
	}

	int sum{};
	for(std::string s; fin >> s; ){
		try{
			sum += std::stoi(s);
		}
		// https://en.cppreference.com/w/cpp/language/attributes
		catch([[maybe_unused]]std::invalid_argument& e){
			// catch the exception
		}
	}
	std::cout << "sum of white space separated integers is " << sum << "\n";

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