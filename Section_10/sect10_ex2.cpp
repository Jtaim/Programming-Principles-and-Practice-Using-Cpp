/*
	Written by Jtaim
	April 5 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Exercise 2
	Write a program that creates a file of data in the form of the temperature
	Reading type defined in section 10.5. For testing, fill the file with at least 50
	"temperature readings". Call this program store_temps.cpp and the file it
	creates raw_temps.txt.

	For the sake of standardization I will hold my naming schema, do the
	program will be sect10_ex2.cpp and the file it creates will be
	sect10_ex2.txt.
*/

#include "../includes/ppp.h"

const std::string file_name{"sect10_ex2.txt"};
constexpr size_t max_readings{50};

// a temperature reading
struct Reading
{
	int hour;               // hour after midnight [0:23]
	double temperature;     // in Fahrenheit
};

constexpr Reading max_read{23,150};
constexpr Reading min_read{0,-100};

Reading random_reading(){
	std::random_device rd;
	//Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> hour_dist(0, 23);
	std::uniform_real_distribution<double> temp_dist(-100, 150);

	return Reading{hour_dist(gen), temp_dist(gen)};
}

// std::ofstream overload
std::ofstream& operator<<(std::ofstream& os, const  Reading& rhs){
	os << std::setfill('0') << std::right << std::setw(2) << rhs.hour << "  "
		<< std::fixed << std::setprecision(2) << rhs.temperature;
	return os;
}

int main()
try{
	std::ofstream fout{file_name};
	if(!fout) ppp::error("Can't open output file ", file_name);
	for(size_t i{}; i < max_readings; ++i){
		auto r{random_reading()};
		if(min_read.hour > r.hour || max_read.hour < r.hour ||
			min_read.temperature > r.temperature || max_read.temperature < r.temperature){
			ppp::error("malformed temperature reading");
		}
		fout << random_reading() << '\n';
	}

	//ppp::keep_window_open();
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