/*
	Written by Jtaim
	Feb 2 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 14
	this is the test program Money class.
*/

#include"../includes/ppp.h"

#include "Money.h"
int main()
try{
	Money m1{"$199.999"};
	std::cout << m1.get_cents() << '\n';

	Money m2{"$5123.5689"};
	std::cout << m2.get_cents() << '\n';

	Money m3{"$0.005"};
	std::cout << m3.get_cents() << '\n';

	Money m4{"$0.004"};
	std::cout << m4.get_cents() << '\n';

	Money m5{"$1"};
	std::cout << m5.get_cents() << '\n';

	Money m6{"$.995"};
	std::cout << m6.get_cents() << '\n';

	//// missing currency type
	//Money m7{".995"};
	//std::cout << m7.get_cents() << '\n';

	//// malformed currency
	//Money m8{"$..995"};
	//std::cout << m8.get_cents() << '\n';

	//// malformed currency
	//Money m9{"$10.995D"};
	//std::cout << m9.get_cents() << '\n';

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