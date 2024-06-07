/*
    Written by Jtaim
    April 5 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Exercise 4
    Modify the store_temps.cpp program from exercise 2 (sect10_ex2.cpp) to include
    a temperature suffix c for Celsius or f for Fahrenheit.

    Modify the temp_stats.cpp program from exercise 3 (sect10_ex3) to test each temperature,
    converting the Celsius readings to Fahrenheit before putting them into the vector.

    For the sake of standardization I will hold my naming schema, the
    program will be sect10_ex4_store.cpp, sect10_ex4_stats.cpp and created file will be sect10_ex4.txt.

    I used the ftoc() function from sect5_ex6.cpp. There are "magic" numbers
    on it, but since they're fixed values on the formula for conversion I don't
    feel the need to make them symbolic constants.
*/

#include "../includes/ppp.hpp"

constexpr std::string_view file_name{ "sect10_ex4.txt" };
constexpr size_t min_readings{ 50 };

constexpr int max_hour{ 23 };
constexpr int min_hour{ 0 };
constexpr int max_temp{ 150 };
constexpr int min_temp{ -100 };

constexpr int fahrenheit{ 0 };
constexpr int celsius{ 1 };
constexpr char celsius_suffix{ 'c' };
constexpr char fahrenheit_suffix{ 'f' };

// a temperature reading
struct Reading
{
    int hour;           // hour after midnight [0:23]
    double temperature; // in Fahrenheit or Celsius
    char suffix;		// to indicate what unit of measure to give
};

// converts Fahrenheit to Celsius
double ftoc( double f )
{
    double fahrenheitToCelsius = 5.0 / 9.0 * ( f - 32.0 );

    if( fahrenheitToCelsius < -273.15 )
    {
        //throw error if value given in Celsius is below -273.15
        ppp::error( "Can not be below absolute zero!\n" );
    }
    return fahrenheitToCelsius;
}

Reading random_reading()
{
    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> hour_dist( 0, 23 );
    std::uniform_real_distribution<double> temp_dist( -100, 150 );
    std::uniform_int_distribution<int> suffix_dist( fahrenheit, celsius );

    auto suffix{ ( suffix_dist( gen ) == fahrenheit ? fahrenheit_suffix : celsius_suffix ) };
    auto random_temp{ temp_dist( gen ) };
    if( celsius_suffix == suffix )
    {
        random_temp = ftoc( random_temp );
    }
    return Reading{ hour_dist( gen ), random_temp, suffix };
}

// std::ofstream std::ostream std::ostringstream overload
template<typename T>
T &operator<<( T &os, const Reading &r )
{
    static_assert( std::is_same<T, std::ostream>::value ||
                   std::is_same<T, std::ofstream>::value ||
                   std::is_same<T, std::ostringstream>::value,
                   "unrecognized or unsupported output stream type in Reading struct" );
    os << std::setfill( '0' ) << std::right << std::setw( 2 ) << r.hour << "  "
        << std::setw( 6 ) << std::fixed << std::setprecision( 2 ) << r.temperature
        << "  " << r.suffix;
    return os;
}

int main()
try
{
    std::ofstream fout{ file_name.data() };
    if( !fout )
    {
        ppp::error( "Can't open output file ", file_name.data() );
    }
    for( size_t i{ 1 }; i <= min_readings; ++i )
    {
        auto r{ random_reading() };
        if( min_hour > r.hour || max_hour < r.hour ||
            min_temp > r.temperature || max_temp < r.temperature )
        {
            ppp::error( "malformed temperature reading" );
        }
        fout << r << "\n";
        std::cout << "Iteration(" << i << ")\t" << r << "\n";
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::cerr << R"(exception: )" << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << R"(exception)";
    ppp::keep_window_open();
    return 2;
}
