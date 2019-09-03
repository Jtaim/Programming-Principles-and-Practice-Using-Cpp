/*
	Written by Jtaim
	Date 11 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 8 Exercise 12
	- Improve print_until_s() from section 8.5.2
*/

#include"../includes/ppp.h"

void print_until_s(const std::vector<std::string>& v, const std::string& quit, int dupsAllowed = 0)
{
	if(!v.empty()){
		auto i{v.cbegin()};
		for(; i != v.end(); ++i){
			if(*i == quit){
				if(dupsAllowed != 0){
					--dupsAllowed;
				} else{
					break;
				}
			}
			std::cout << *i << ", ";
		}
		if(i == v.cend()){
			std::cout << "No " << quit << " found.";
		}
	} else{
		std::cout << "no strings found";
	}
	std::cout << "\n";
}

int main()
{
	std::vector<std::string> v1{"zero","one", "two", "zero", "two", "three", "four"};
	std::vector<std::string> v2{};

	const std::string quit{"two"};

	std::cout << "numbers: ";
	print_until_s(v1, quit);

	std::cout << "numbers: ";
	print_until_s(v1, quit, 1);
	
	std::cout << "numbers: ";
	print_until_s(v2, quit, 1);

	ppp::keep_window_open();
	return 0;
}
