/*
	Written by Jtaim
	Feb 9 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 15
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

	/*Money m7{".995"};
	std::cout << m7.get_cents() << '\n';*/

	/*Money m8{"$..995"};
	std::cout << m8.get_cents() << '\n';*/

	Money m9{"USD104.995"};
	std::cout << m9.get_cents() << '\n';

	Money m10{"DKK109.995"};
	std::cout << m10.get_cents() << '\n';

	Money m11{"Kr129.995"};
	std::cout << m11.get_cents() << '\n';

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