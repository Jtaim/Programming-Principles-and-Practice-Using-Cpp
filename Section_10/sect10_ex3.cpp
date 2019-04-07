/*
	Written by Jtaim
	April 6 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Exercise 3
	Write a program that reads the data from the raw_temps.txt created in exercise 2
	into a vector and then calculates the mean and median temperatures in your data set.
	Call this program temp_stats.cpp.

	For the sake of standardization I will hold my naming schema, do the
	program will be sect10_ex3.cpp and the file it created in exercise 2 was
	sect10_ex2.txt.

	For the mean and median function I referenced section 4 exercise 2
*/

#include "../includes/ppp.h"

const std::string file_name{"sect10_ex2.txt"};

struct Reading
{
	int hour{};               // hour after midnight [0:23]
	double temperature{};     // in Fahrenheit
};

constexpr Reading max_read{23,150};
constexpr Reading min_read{0,-100};

//operator>>
std::ifstream& operator>>(std::ifstream& in, Reading& rhs){
	in.exceptions(in.exceptions() | std::ios::badbit);
	decltype(Reading::hour) h{};
	decltype(Reading::temperature) t{};
	in >> h >> t;
	if(in.fail()) return in;
	if(min_read.hour > h || max_read.hour < h ||
		min_read.temperature > t || max_read.temperature < t){
		in.clear(std::ios_base::failbit);
		return in;
	}
	rhs = Reading{h,t};

	return in;
}

// compute mean temperature:
double getTemperatureMean(std::vector<Reading>& rhs){
	if(rhs.empty()) return 0.0;
	double sum = std::accumulate(rhs.begin(), rhs.end(), 0.0,
		[](double a, const Reading& b){return a + b.temperature; });
	return sum / rhs.size();
}

// compute median temperature:
// If n is odd then Median (M) = value of ((n + 1)/2)th item term.
// If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
double getTemperatureMedian(std::vector<Reading>& rhs){
	if(rhs.empty()) return 0.0;
	std::sort(rhs.begin(), rhs.end(),
		[](const Reading& a, const Reading& b){return a.temperature > b.temperature; });

	if((rhs.size() % 2) > 0){
		return rhs.at(rhs.size() / 2).temperature;
	}
	else{
		// if have even amount, remember vector index starts at zero
		// get 2 middle indexes and divide by 2
		return (rhs.at(rhs.size() / 2 - 1).temperature + rhs.at(rhs.size() / 2).temperature) / 2;
	}
}

int main()
try{
	std::ifstream fin{file_name};
	if(!fin) ppp::error("Can't open output file ", file_name);
	std::vector<Reading> readings;
	for(Reading r; fin >> r;){
		readings.push_back(r);
	}
	if(fin.eof()) fin.clear();
	if(fin.fail()) ppp::error("file stream failed");

	std::cout << "Average number: " << getTemperatureMean(readings) << "\n";
	std::cout << "Median number: " << getTemperatureMedian(readings) << "\n";

	ppp::keep_window_open();
	return 0;
}
catch(std::exception & e){
	std::cerr << R"(exception: )" << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << R"(exception)";
	ppp::keep_window_open();
	return 2;
}