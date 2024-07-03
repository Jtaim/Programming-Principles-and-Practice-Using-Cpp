/*
    Written by Jtaim
    Date 1 July 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 15
    Write a program that reads a file of whitespace-separated numbers and
    outputs a file of numbers using scientific format and
    precision 8 in four fields of 20 characters per line.
*/

#include "ppp.hpp"
#include <print>

static double getRandomNumber()
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen( rd() ); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib( 1, 10000 );
    std::uniform_int_distribution<> scale( 0, 5 );

    // Use distrib to transform the random unsigned int and scale into a double
    switch( scale( gen ) )
    {
        case 1:
            return distrib( gen ) / 10.0;
        case 2:
            return distrib( gen ) / 100.0;
        case 3:
            return distrib( gen ) / 1000.0;
        case 4:
            return distrib( gen ) / 10000.0;
        case 5:
            return distrib( gen ) / 100000.0;
        default:
            return distrib( gen ) / 1.0;
    }
}

constexpr std::string_view numbers{ "sect11_ex15_numbers.txt" };
constexpr std::string_view formatted_numbers{ "sect11_ex15_formatted_numbers.txt" };

int main()
try
{
    std::ofstream ofs{ numbers.data() };
    if( !ofs )
    {
        ppp::error( std::format( "could not open {}", numbers.data() ) );
    }
    for( int n = 0; n != 1000; ++n )
    {
        ofs << getRandomNumber() << ' ';
    }
    ofs.close();

    std::ifstream ifs{ numbers.data() };   // read a file of whitespace-separated numbers
    if( !ifs )
    {
        ppp::error( std::format( "could not open {}", numbers.data() ) );
    }
    ofs.open( formatted_numbers.data() );  // create a file for formatted numbers
    if( !ofs )
    {
        ppp::error( std::format( "could not open {}", formatted_numbers.data() ) );
    }
    std::size_t counter{ 1 };               // used to set columns
    for( double d; ifs >> d; ++counter )
    {
        // set precision to 8
        // 4 columns of minimum space of 20
        ofs << std::format( "{:<20.8e}{}", d, ( !( counter % 4 ) ? '\n' : ' ' ) );
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::println( "exception: {}", e.what() );
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::println( "exception" );
    ppp::keep_window_open();
    return 2;
}
