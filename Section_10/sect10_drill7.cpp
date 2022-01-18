/*
	Written by Jtaim
	Mar 24 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Drill 7
	Compare the two vectors and print Something's wrong! if the number of elements or the values of elements differ.
*/

#include "../includes/ppp.h"
#include "Point.h"

int main()
try{
	constexpr size_t how_many{7};
	const std::string point_file{"mydata.txt"};

	std::cout << "Enter seven (x,y) pairs:\n";
	std::vector<Point<int>> original_points;
	std::ofstream fout{point_file};

	if(!fout){
		ppp::error("Can't open output file ", point_file);
	}
	for(size_t i{}; i < how_many; ++i){
		decltype(original_points.begin())::value_type p{};
		while(!(std::cin >> p)){
			if(std::cin.eof()){
				ppp::error("EOF found before filling required data");
			}
			std::cout << "bad input try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
		original_points.push_back(p);
		fout << p;
	}
	fout.close();

	//processed_points;
	std::ifstream fin{point_file};
	if(!fin){
		ppp::error("Can't open input file ", point_file);
	}
	std::vector<Point<int>> processed_points;
	decltype(processed_points.begin())::value_type p{};
	for(size_t i{}; (fin >> p) && i < /*how_many*/2; ++i){
		processed_points.push_back(p);
	}

	std::cout << "From user points:\n";
	for(const auto& po : original_points){
		std::cout << po << "\n";
	}
	std::cout << "From file points:\n";
	for(const auto& pf : processed_points){
		std::cout << pf << "\n";
	}

	if(!(original_points.size() == processed_points.size())){
		std::cout << "Something's wrong!";
	}

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