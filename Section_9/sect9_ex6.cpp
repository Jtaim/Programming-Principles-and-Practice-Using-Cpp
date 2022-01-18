/*
	Written by Jtaim
	Date 20 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 6
	Design and implement a Book class under library namespace
	- add == operator to for ISBNs
	- add != operator to for ISBNs
	- add << to print title, author, and ISBN on separate lines
*/

#include"../includes/ppp.h"

#include "Book.h"

int main()
try{
	library::Book book1("0-321-99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);
	std::cout << book1 << "\n\n";
	library::Book book2;
	library::Book book3 = book1;

	if(book1 == book3){
		std::cout << book3 << "\n\n";
	}

	if(book1 != book2){
		std::cout << book2 << "\n\n";
	}

	//library::Book book4("0-321_99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);

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