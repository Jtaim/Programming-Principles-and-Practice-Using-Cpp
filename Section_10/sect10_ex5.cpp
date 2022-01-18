/*
	Written by Jtaim
	April 7 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Exercise 5
	Write the function print_year() mentioned in section 10.11.2.

	fixed to handle invalid month name in Month operator>> function with exception.
*/

#include "../includes/ppp.h"

constexpr auto not_a_reading{std::numeric_limits<double>::min()};	// less than absolute zero
constexpr auto not_a_month{std::numeric_limits<ptrdiff_t>::min()};
// limits for temperature readings
constexpr int implausible_min{-200};
constexpr int implausible_max{200};

constexpr std::array<std::string_view, 12> month_input_tbl{
		   "jan", "feb", "mar", "apr", "may", "jun", "jul",
		   "aug", "sep", "oct", "nov", "dec"
};

constexpr std::array<std::string_view, 12> month_print_tbl{
		  "January", "February", "March", "April", "May", "June", "July",
		  "August", "September", "October", "November", "December"
};

// find name of a month? 
// If found return its index [0:11]
// If not found return std::numeric_limits<ptrdiff_t>::min()
ptrdiff_t month_to_int(std::string s)
{
	auto itr{find(month_input_tbl.begin(), month_input_tbl.cend(), s)};
	if(itr != month_input_tbl.cend()){
		return (itr - month_input_tbl.cbegin());
	}
	return not_a_month;
}

// find Month name via a offset
// If found returns string from an array from the an index [0:11] given
// out_of_range exception for incorrect index
std::string int_to_month(ptrdiff_t i)
{
	if(i < 0 || i > 11){
		throw std::out_of_range("invalid index for month_print_table");
	}
	return month_print_tbl.at(i).data();
}

struct Day
{
	std::vector<double> hour{std::vector<double>(24,not_a_reading)};
};

struct Month
{									// a month of temperature readings
	ptrdiff_t month{not_a_month};	// [0:11] January is 0
	std::vector<Day> day{32};		// [1:31] one vector of readings per day
};

struct Year
{									// a year of temperature readings, organized by month
	int year;						// positive == A.D.
	std::vector<Month> month{12};	// [0:11] January is 0
};

struct Reading
{
	int day{std::numeric_limits<int>::max()};
	int hour{std::numeric_limits<int>::max()};
	double temperature;
};

bool is_valid(const Reading& r)
// a rough test
{
	if(r.day < 1 || 31 < r.day ||
		r.hour < 0 || 23 < r.hour ||
		r.temperature < implausible_min || implausible_max < r.temperature){
		return false;
	}
	return true;
}

std::istream& find_tag(std::istream& ist, const char tag)
{
	char c{};
	ist >> c;
	if(ist.fail() || c != tag){
		ist.unget();
		ist.clear(std::ios_base::failbit);	// invalid open or close tag
	}
	return ist;
}

std::istream& operator>>(std::istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, but don’t bother with data validity
{
	if(!find_tag(is, '(')){
		return is;
	}
	int d{};
	int h{};
	double t{};
	is >> d >> h >> t;
	if(!is){
		ppp::error("unexpected readings");
	}
	if(!find_tag(is, ')')){
		ppp::error("expected reading close tag ')'");
	}
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

std::istream& operator>>(std::istream& is, Month& m)
// read a month from is into m
// format: { month feb . . . }
{
	if(!find_tag(is, '{')){
		return is;
	}
	std::string month_marker;
	std::string mm;
	is >> month_marker >> mm;
	if(!is || month_marker != "month"){
		ppp::error("invalid tag for \"month\"");
	}
	m.month = month_to_int(mm);
	if(not_a_month == m.month){
		ppp::error("invalid index for month_to_int()");
	}

	for(Reading r; is >> r; ){
		if(!is_valid(r)){
			ppp::error("Reading is invalid");
		}
		m.day.at(r.day).hour.at(r.hour) = r.temperature;
	}
	is.clear();	// clear did not find another reading
	if(!find_tag(is, '}')){
		ppp::error("expected month close tag '}'");
	}
	return is;
}

std::istream& operator>>(std::istream& is, Year& y)
// read a year from is into y
// format: { year 1972 . . . }
{
	if(!find_tag(is, '{')){
		return is;
	}
	std::string year_marker;
	int yy{};
	is >> year_marker >> yy;
	if(!is || year_marker != "year"){
		ppp::error("invalid tag for \"year\"");
	}
	y.year = yy;

	for(Month m; is >> m; m = Month{}){
		y.month.at(m.month) = m;
	}
	is.clear();	// clear did not find another month
	if(!find_tag(is, '}')){
		ppp::error("expected year close tag '}'");
	}
	return is;
}

std::ofstream& operator<<(std::ofstream& out, const Year& y)
{
	out << std::setw(6) << std::left << "year:"
		<< y.year << "\n";
	for(auto m{y.month.cbegin()}; m < y.month.cend(); ++m){
		if(not_a_month != m->month){
			out << std::setw(4) << " "
				<< std::setw(7) << "month:"
				<< int_to_month(m->month) << "\n";
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
							<< std::setprecision(5) << *h << "\n";
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
	std::string iname{"sect10_ex5_in.txt"};
	//std::cin >> iname;
	std::ifstream fin{iname};
	if(!fin){
		ppp::error("can't open input file", iname);
	}
	fin.exceptions(fin.exceptions() | std::ios_base::badbit);	// throw for bad()

	// open an output file:
	std::cout << "Please enter output file name\n";
	std::string oname{"sect10_ex5_out.txt"};
	//std::cin >> oname;
	std::ofstream fout{oname};
	if(!fout){
		ppp::error("can't open output file", oname);
	}

	 // read an arbitrary number of years:
	std::vector<Year> ys;
	for(Year y; fin >> y; y = Year{}){	// get a freshly initialized Year each time around
		ys.push_back(y);
	}
	std::cout << "read " << ys.size() << " years of readings\n";
	for(Year& y : ys){
		fout << y << "\n";
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
