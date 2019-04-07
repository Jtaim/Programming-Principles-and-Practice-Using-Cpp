/*
	Written by Jtaim
	April 6 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Exercise 4
	Modify the temp_stats.cpp program from exercise 3 to test each temperature,
	converting the Celsius readings to Fahrenheit before putting them into the vector.

	Section 10 Exercise 3
	Write a program that reads the data from the raw_temps.txt created in exercise 2
	into a vector and then calculates the mean and median temperatures in your data set.
	Call this program temp_stats.cpp.

	For the sake of standardization I will hold my naming schema, the
	program will be sect10_ex4_stats.cpp and the file created from sect10_ex4_store.cpp
	is sect10_ex4.txt.

	I used the ctof() function from sect5_ex6.cpp. There are "magic" numbers
	on it, but since they're fixed values on the formula for conversion I don't
	feel the need to make them symbolic constants.
*/

#include "../includes/ppp.h"

const std::string file_name{"sect10_ex4.txt"};

// a temperature reading
struct Reading
{
	int hour;           // hour after midnight [0:23]
	double temperature; // in Fahrenheit or Celsius
	char suffix;		// to indicate what unit of measure to give
};

constexpr int max_hour{23};
constexpr int min_hour{0};
constexpr int max_temp{150};
constexpr int min_temp{-100};
constexpr char celsius_suffix{'c'};
constexpr char fahrenheit_suffix{'f'};

// converts Celsius to Fahrenheit
double ctof(double c){
	if(c < -273.15){
		//throw error if value given in Celsius is below -273.15
		ppp::error("Can not be below absolute zero!\n");
	}
	double celsiusToFahrenheit = 9.0 / 5.0 * c + 32.0;
	return celsiusToFahrenheit;
}

//operator>>
std::ifstream& operator>>(std::ifstream& in, Reading& rhs){
	in.exceptions(in.exceptions() | std::ios::badbit);
	decltype(Reading::hour) h{};
	decltype(Reading::temperature) t{};
	char suffix{};
	in >> h >> t >> suffix;
	if(in.fail()) return in;
	if(suffix == celsius_suffix){
		t = ctof(t);
	}
	if(min_hour > h || max_hour < h ||
		min_temp > t || max_temp < t){
		in.clear(std::ios_base::failbit);
		return in;
	}
	rhs = Reading{h,t,fahrenheit_suffix};

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