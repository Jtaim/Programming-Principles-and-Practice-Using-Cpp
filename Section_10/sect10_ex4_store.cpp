/*
	Written by Jtaim
	April 5 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 10 Exercise 4
	Modify the store_temps.cpp program from exercise 2 to include a temperature
	suffix c for Celsius or f for Fahrenheit.
	Section 10 Exercise 2
	Write a program that creates a file of data in the form of the temperature
	Reading type defined in section 10.5. For testing, fill the file with at least 50
	"temperature readings". Call this program store_temps.cpp and the file it
	creates raw_temps.txt.

	For the sake of standardization I will hold my naming schema, the
	program will be sect10_ex4_store.cpp and the file it creates will be
	sect10_ex4.txt.

	I used the ftoc() function from sect5_ex6.cpp. There are "magic" numbers
	on it, but since they're fixed values on the formula for conversion I don't
	feel the need to make them symbolic constants.
*/

#include "../includes/ppp.h"

const std::string file_name{"sect10_ex4.txt"};
constexpr size_t max_readings{50};
constexpr int max_hour{23};
constexpr int min_hour{0};
constexpr int max_temp{150};
constexpr int min_temp{-100};
constexpr int fahrenheit{0};
constexpr int celsius{1};
constexpr char celsius_suffix{'c'};
constexpr char fahrenheit_suffix{'f'};

// a temperature reading
struct Reading
{
	int hour;           // hour after midnight [0:23]
	double temperature; // in Fahrenheit or Celsius
	char suffix;		// to indicate what unit of measure to give
};

Reading random_reading(){
	std::random_device rd;
	//Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> hour_dist(0, 23);
	std::uniform_real_distribution<double> temp_dist(-100, 150);
	std::uniform_int_distribution<int> suffix_dist(fahrenheit, celsius);

	auto suffix{(suffix_dist(gen) == 0 ? fahrenheit_suffix : celsius_suffix)};
	// leaving the temp as Fahrenheit and let main() deal with the conversion
	return Reading{hour_dist(gen), temp_dist(gen), suffix};
}

// std::ofstream overload
std::ofstream& operator<<(std::ofstream& os, const  Reading& rhs){
	// temperatures are store natively as Fahrenheit
	os << std::right << std::setw(2) << rhs.hour << "  "
		<< std::setw(6) << std::fixed << std::setprecision(2) << rhs.temperature
		<< "  " << rhs.suffix;
	return os;
}

// converts Fahrenheit to Celsius
double ftoc(double f){
	double fahrenheitToCelsius = 5.0 / 9.0 * (f - 32.0);

	if(fahrenheitToCelsius < -273.15){
		//throw error if value given in Celsius is below -273.15
		ppp::error("Can not be below absolute zero!\n");
	}
	return fahrenheitToCelsius;
}

int main()
try{
	std::ofstream fout{file_name};
	if(!fout) ppp::error("Can't open output file ", file_name);
	for(size_t i{}; i < max_readings; ++i){
		auto r{random_reading()};
		if(min_hour > r.hour || max_hour < r.hour ||
			min_temp > r.temperature || max_temp < r.temperature){
			ppp::error("malformed temperature reading");
		}
		if(r.suffix == celsius_suffix){
			r.temperature = ftoc(r.temperature);
		}
		fout << r << "\n";
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