/*
	Written by Jtaim
	Mar 24 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Drill 3
	Print the data in original_points to see what it looks like.
*/

#include "../includes/ppp.h"
#include "Point.h"

int main()
try{
	constexpr size_t how_many{7};

	std::cout << "Enter seven (x,y) pairs:\n";
	std::array<Point<int>, how_many> points;

	for(auto& p : points){
		while(!(std::cin >> p)){
			if(std::cin.eof()){
				ppp::error("EOF found before filling required data");
			}
			std::cout << "bad input try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
	}

	for(const auto& p : points){
		std::cout << p << "\n";
	}

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