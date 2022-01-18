/*
	Written by Jtaim
	Date 20 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 8
	Design and implement a Patron class under library namespace
*/

#include"../includes/ppp.h"

#include "Patron.h"

int main()
try{
	library::Patron patron{"John Doe", 123456};
	if(!patron.is_outstanding_fee()){
		std::cout << patron.get_name() << " outstanding fees $" << patron.get_fees() << '\n';
	}

	patron.set_fees(0.01);
	std::cout << patron.get_name() << " outstanding fee of $" << patron.get_fees() << '\n';


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