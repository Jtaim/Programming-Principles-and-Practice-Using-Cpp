/*
	Written by Jtaim
	Mar 24 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Drill 5
	Close the ofstream and then open an ifstream for mydata.txt.
	Read the data from mydata.txt and store it in a new vector called processed_points.
*/

#include "../includes/ppp.h"
#include "Point.h"

int main()
try{
	constexpr size_t how_many{7};
	const std::string point_file{"mydata.txt"};

	std::cout << "Enter seven (x,y) pairs:\n";
	std::array<Point<int>, how_many> points;
	std::ofstream fout{point_file};

	if(!fout){
		ppp::error("Can't open output file ", point_file);
	}
	for(auto& p : points){
		while(!(std::cin >> p)){
			if(std::cin.eof()){
				ppp::error("EOF found before filling required data");
			}
			std::cout << "bad input try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
		fout << p;
	}
	fout.close();

	//processed_points;
	std::ifstream fin{point_file};
	if(!fin){
		ppp::error("Can't open input file ", point_file);
	}
	std::vector<decltype(points.begin())::value_type> from_file_points;
	decltype(points.begin())::value_type pf{};
	while(fin >> pf){
		from_file_points.push_back(pf);
	}

	for(const auto& pv : from_file_points){
		std::cout << pv << "\n";
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