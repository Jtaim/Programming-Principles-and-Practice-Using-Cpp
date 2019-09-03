/*
	Written by Jtaim
	Date 20 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 5
	Design and implement a Book class under library namespace
	-
*/

#include"../includes/ppp.h"

#include "Book.h"

int main()
try{
	library::Book book("0-321-99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);
	std::cout << "ISBN: " << book.get_isbn() << '\n'
		<< "TITLE: " << book.get_title() << '\n'
		<< "AUTHOR: " << book.get_author() << '\n'
		<< "COPYRIGHT: " << book.get_copyright() << '\n'
		<< "checked out: " << std::boolalpha << book.is_checked_out() << "\n\n";

	book.check_inout(true);
	std::cout << "ISBN: " << book.get_isbn() << '\n'
		<< "TITLE: " << book.get_title() << '\n'
		<< "AUTHOR: " << book.get_author() << '\n'
		<< "COPYRIGHT: " << book.get_copyright() << '\n'
		<< "checked out: " << std::boolalpha << book.is_checked_out() << "\n\n";

	//library::Book book2("0-321_99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);

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