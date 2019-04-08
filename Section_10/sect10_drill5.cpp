/*
	Written by Jtaim
	Mar 24 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Drill 4
	Test program Point class. Using iostream operation for Point class.
	Save Point data to a file.
	Read data back from file and tore in a vector
*/

#include "../includes/ppp.h"
#include "Point.h"

using point_type = std::vector<Point<int>>;

int main()
try{
	constexpr point_type::size_type HOW_MANY{7};
	const std::string FILE{"sect10_drill_data.txt"};

	std::cout << "Enter seven (x,y) pairs:\n";
	point_type original_points;
	std::ofstream fout{FILE};

	if(!fout) ppp::error("Can't open output file ", FILE);
	while(original_points.size() < HOW_MANY){
		point_type::value_type point;
		if(!(std::cin >> point)){
			if(std::cin.eof()){
				std::cout << "EOF found before getting required data amount\n";
				break;
			}
			std::cout << "bad input try again\n";
			ppp::clear_cin_buffer();
		}
		else{
			original_points.push_back(point);
			fout << point;
		}
	}

	fout.close();

	point_type processed_points;
	std::ifstream fin{FILE};

	if(!fin) ppp::error("Can't open input file ", FILE);
	while(processed_points.size() < HOW_MANY){
		point_type::value_type point;
		if(!(fin >> point)){
			if(fin.eof()){
				std::cout << "EOF found before reading required data amount";
				break;
			}
			if(fin.fail()) ppp::error("bad input data");
		}
		else{
			processed_points.push_back(point);
		}
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