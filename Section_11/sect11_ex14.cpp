/*
    Written by Jtaim
    Date 30 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 14
    Write a program that reads a text file and writes out how many characters of each character
    classification are in the file, refer to section 11.6.
*/

#include "ppp.hpp"
#include <print>

using Function = int( * )( int );

struct Classification_Functions
{
    Function funtion{};
    std::string_view name;
    int total_found_classification{};
};

std::array char_classification
{
    Classification_Functions{std::isalnum,"number"},
    Classification_Functions{std::isalpha,"alpha_numeric"},
    Classification_Functions{std::isblank,"blank"},
    Classification_Functions{std::iscntrl,"control"},
    Classification_Functions{std::isdigit,"digit"},
    Classification_Functions{std::isgraph,"graph"},
    Classification_Functions{std::islower,"lower_case"},
    Classification_Functions{std::isprint,"print"},
    Classification_Functions{std::ispunct,"punctuation"},
    Classification_Functions{std::isspace,"space"},
    Classification_Functions{std::isupper,"upper_case"},
    Classification_Functions{std::isxdigit,"hex_digit"}
};

constexpr std::string_view file{ "sect11_ex14.cpp" };

int main()
try
{
    std::ifstream ifs{ file.data()};
    if( !ifs )
    {
        ppp::error( std::format( "could not open {}", file.data() ) );
    }
    for( char c{}; ifs.get( c ); )
    {
        for( auto &f : char_classification )
        {
            if( f.funtion( static_cast<unsigned char>( c ) ) )
            {
                f.total_found_classification += 1;
            }
        }
    }

    std::println( "{:15}| {}", "Classification", "Found" );
    std::println( "{:_<25}", '_' );
    for( auto &f : char_classification )
    {
        std::println( "{:15}| {}", f.name, f.total_found_classification );
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
