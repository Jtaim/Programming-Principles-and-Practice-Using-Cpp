/*
	Written by Jtaim
	April 7 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Exercise 5
	Write the function print_year() mentioned in §10.11.2.

	fixed to handle invalid month name in Month operator>> function with exception.
*/

#include "../includes/ppp.h"

constexpr int not_a_reading = -7777;	// less than absolute zero
constexpr int not_a_month = -1;

const std::vector<std::string> month_input_tbl = {
		   "jan", "feb", "mar", "apr", "may", "jun", "jul",
		   "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(std::string s)
// is s the name of a month? If so return its index [0:11] otherwise –1
{
	for(int i = 0; i < 12; ++i){
		if(month_input_tbl.at(i) == s){
			return i;
		}
	}
	return -1;
}

const std::vector<std::string> month_print_tbl = {
		  "January", "February", "March", "April", "May", "June", "July",
		  "August", "September", "October", "November", "December"
};

std::string int_to_month(int i)
// months [0:11]
{
	if(i < 0 || 12 <= i) ppp::error("bad month index");
	return month_print_tbl.at(i);
}

struct Day
{
	std::vector<double> hour{std::vector<double>(24,not_a_reading)};
};

struct Month
{                               // a month of temperature readings
	int month{not_a_month};		// [0:11] January is 0
	std::vector<Day> day{32};   // [1:31] one vector of readings per day
};

struct Year
{									// a year of temperature readings, organized by month
	int year;						// positive == A.D.
	std::vector<Month> month{12};	// [0:11] January is 0
};

// limits for temperature readings
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

struct Reading
{
	int day;
	int hour;
	double temperature;
};

bool is_valid(const Reading& r)
// a rough test
{
	if(r.day < 1 || 31 < r.day) return false;
	if(r.hour < 0 || 23 < r.hour) return false;
	if(r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

std::istream & operator>>(std::istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, but don’t bother with data validity
{
	char ch1;
	if(is >> ch1 && ch1 != '('){	// could it be a Reading?
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if(!is || ch2 != ')') ppp::error("bad reading");	// messed-up reading
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

//ist.exceptions(ist.exceptions() | ios_base::badbit);
void end_of_loop(std::istream& ist, char term, const std::string& message){
	if(ist.fail()){                // use term as terminator and/or separator
		ist.clear();
		char ch{};
		if(ist >> ch && ch == term) return;             // all is fine
		ppp::error(message);
	}
}

std::istream& operator>>(std::istream& is, Month& m)
// read a month from is into m
// format: { month feb . . . }
{
	char ch{};
	if(is >> ch && ch != '{'){
		is.unget();
		is.clear(std::ios_base::failbit);                  // we failed to read a Month
		return is;
	}
	std::string month_marker;
	std::string mm;
	is >> month_marker >> mm;
	if(!is || month_marker != "month") ppp::error("bad start of month");
	m.month = month_to_int(mm);
	if(-1 == m.month) ppp::error("invalid month name!");
	int duplicates{};
	int invalids{};
	for(Reading r; is >> r; ){
		if(is_valid(r)){
			if(m.day.at(r.day).hour.at(r.hour) != not_a_reading)
				++duplicates;
			m.day.at(r.day).hour.at(r.hour) = r.temperature;
		}
		else
			++invalids;
	}
	if(invalids) ppp::error("invalid readings in month", invalids);
	if(duplicates) ppp::error("duplicate readings in month", duplicates);
	end_of_loop(is, '}', "bad end of month");
	return is;
}

std::istream& operator>>(std::istream& is, Year& y)
// read a year from is into y
// format: { year 1972 . . . }
{
	char ch{};
	is >> ch;
	if(ch != '{'){
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}
	std::string year_marker;
	int yy{};
	is >> year_marker >> yy;
	if(!is || year_marker != "year") ppp::error("bad start of year");
	y.year = yy;
	for(Month m; is >> m; ){
		y.month.at(m.month) = m;
		m = Month{}; // “reinitialize” m
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}

std::ofstream& operator<<(std::ofstream& out, const Year& y){
	out << std::setw(6) << std::left << "year:"
		<< y.year << "\n";
	for(auto m{y.month.cbegin()}; m < y.month.cend(); ++m){
		if(not_a_month != m->month){
			out << std::setw(4) << " "
				<< std::setw(7) << "month:"
				<< month_print_tbl.at(m - y.month.cbegin()) << "\n";
			for(auto d{m->day.begin()}; d < m->day.end(); ++d){
				// oss is a temporary stream to deal with not printing days of no data
				std::ostringstream oss;
				oss << std::setw(8) << std::left << " " 
					<< std::setw(5) << "day:"
					<< d - m->day.begin() << "\n";
				bool hr_data{false};
				for(auto h{d->hour.begin()}; h < d->hour.end(); ++h){
					if(not_a_reading != *h){
						hr_data = true;	// found hour data
						oss << std::setw(12) << " "
							<< std::setw(6) << "hour:"
							<< h - d->hour.begin() << "\n"
							<< std::setw(16) << " "
							<< std::setw(6) << "temp:"
							<< std::setprecision(2) << *h << "\n";
					}
				}
				if(hr_data) out << oss.str();	// print hours and days with data
			}
		}
	}
	return out;
}

int main()
try{
	// open an input file:
	std::cout << "Please enter input file name\n";
	std::string iname = "sect10_ex5_in.txt";
	//std::cin >> iname;
	std::ifstream fin{iname};
	if(!fin) ppp::error("can't open input file", iname);
	fin.exceptions(fin.exceptions() | std::ios_base::badbit);	// throw for bad()
	// open an output file:
	std::cout << "Please enter output file name\n";
	std::string oname = "sect10_ex5_out.txt";
	//std::cin >> oname;
	std::ofstream fout{oname};
	if(!fout) ppp::error("can't open output file", oname);

	 // read an arbitrary number of years:
	std::vector<Year> ys;
	while(true){
		Year y;                  // get a freshly initialized Year each time around
		if(!(fin >> y)) break;
		ys.push_back(y);
	}
	std::cout << "read " << ys.size() << " years of readings\n";
	for(Year& y : ys) fout << y << "\n";

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
