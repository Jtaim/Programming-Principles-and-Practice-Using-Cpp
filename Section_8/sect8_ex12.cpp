/*
	Written by Jtaim
	Date 11 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 8 Exercise 12
	- Improve print_until_s() from section 8.5.2
*/

#include"../includes/ppp.h"

void print_until_s(const std::vector<std::string>& v, const std::string& quit)
{
	if(!v.empty()){
		for(const std::string& s : v){
			if(s == quit){
				return;
			}
			std::cout << s << '\n';
		}
		std::cout << "No " << quit << " found.\n";
	}
}

void print_until_ss(const std::vector<std::string>& v, const std::string& quit)
{
	if(!v.empty()){
		int count{};
		for(const std::string& s : v){
			if(s == quit){
				if(count >= 1){
					return;
				}
				++count;
			}
			std::cout << s << '\n';
		}
		if(count == 0){
			std::cout << "No " << quit << " found.\n";
		}
	}
}

int main()
{
	std::string quit{"zero"};
	std::vector<std::string> vs{"numbers:", "zero","one", "two", "zero", "three", "four"};
	print_until_s(vs, quit);

	print_until_ss(vs, quit);

	ppp::keep_window_open();
	return 0;
}