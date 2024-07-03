/*
    Written by Jtaim
    Date 1 July 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 16
    Write a program to read a file of whitespace-separated numbers and
    output them in order (lowest value first), one value per line.
    Write a value only once, and if it occurs more than once write the count of its occurrences on its line.
    For example, 7 5 5 7 3 117 5 should give
    3
    5 3
    7 2
    117
*/

#include "ppp.hpp"
#include <print>

static double getRandomNumber()
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen( rd() ); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib( 1, 100 );

    return distrib( gen );
}

constexpr std::string_view numbers_file{ "sect11_ex16_numbers.txt" };

struct number_count
{
    int number;
    int count;
    bool operator==( int i ) { return i == number; };
};

int main()
try
{
    std::ofstream ofs{ numbers_file.data() };
    if( !ofs )
    {
        ppp::error( std::format( "could not open {}", numbers_file.data() ) );
    }
    for( int n = 0; n != 1000; ++n )            // get random number
    {
        ofs << getRandomNumber() << ' ';
    }
    ofs.close();

    std::ifstream ifs{ numbers_file.data() };   // read a file of whitespace-separated numbers
    if( !ifs )
    {
        ppp::error( std::format( "could not open {}", numbers_file.data() ) );
    }

    std::vector<number_count> numbers;
    for( int i; ifs >> i; )
    {
        auto index = std::find( numbers.begin(), numbers.end(), i );
        if( index == numbers.end() )
        {
            numbers.push_back( number_count{ i, 1 } );
        }
        else
        {
            ++index->count;
        }
    }
    
    std::sort( numbers.begin(), numbers.end(), []( auto a, auto b ) { return a.number < b.number; } );
    for( const auto &nc : numbers )
    {
        std::println( "{:4} {}", nc.number, nc.count != 1 ? std::to_string(nc.count) :" ");
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
