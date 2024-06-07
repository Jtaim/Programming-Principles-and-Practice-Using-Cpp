/*
    Written by Jtaim
    April 5 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Exercise 2
    Write a program that creates a file of data in the form of the temperature
    Reading type defined in section 10.5. For testing, fill the file with at least 50 "temperature readings".
    Call this program store_temps.cpp and the file it creates raw_temps.txt.

    For the sake of standardization I will hold my naming schema, the
    program will be sect10_ex2.cpp and the file it creates will be
    sect10_ex2.txt.
*/

#include "../includes/ppp.hpp"

constexpr std::string_view file_name{ "sect10_ex2.txt" };
constexpr size_t min_readings{ 50 };

// a temperature reading
struct Reading
{
    int hour;               // hour after midnight [0:23]
    double temperature;     // in Fahrenheit
};

constexpr Reading max_read{ 23,150 };
constexpr Reading min_read{ 0,-100 };

Reading random_reading()
{
    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> hour_dist( 0, 23 );
    std::uniform_real_distribution<double> temp_dist( -100.0, 150.0 );

    return Reading{ hour_dist( gen ), temp_dist( gen ) };
}

// std::ofstream overload
template<typename T>
T &operator<<( T &os, const Reading &r )
{
    static_assert( std::is_same<T, std::ostream>::value ||
                   std::is_same<T, std::ofstream>::value ||
                   std::is_same<T, std::ostringstream>::value,
                   "unrecognized or unsupported output stream type in Reading struct" );
    os << std::setfill( '0' ) << std::right << std::setw( 2 ) << r.hour << "  "
        << std::fixed << std::setprecision( 2 ) << r.temperature;
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
        Reading r{ random_reading() };
        if( min_read.hour > r.hour || max_read.hour < r.hour ||
            min_read.temperature > r.temperature || max_read.temperature < r.temperature )
        {
            ppp::error( "malformed temperature reading" );
        }
        fout << r/*random_reading()*/ << '\n';
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
