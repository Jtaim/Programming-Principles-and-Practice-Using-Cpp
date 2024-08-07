/*
    Written by Jtaim
    Date 21 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 5
    Write a program that reads strings and for each string outputs the character classification of each character,
    as defined by the character classification functions presented in section 11.6.
    Note that a character can have several classifications (e.g., x is both a letter and an alphanumeric).
*/

#include "ppp.hpp"
#include <print>
 
using Function = int( * )( int );

struct Classification_Functions
{
    Function funtion;
    std::string_view name;
};

constexpr std::array char_classification
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

int main()
try
{
    std::ifstream ifs{ "sect11_ex5.cpp" };
    for( char c{}; ifs.get( c ); )
    {
        std::print("{} (int)c {:#0x} is a ", (c == 0xa ? ' ' : c ), static_cast<int>( c ));  // to keep output lined up linefeed is a space
        for( const auto &f : char_classification )
        {
            if( f.funtion( static_cast<unsigned char>( c ) ) )
            {
                std::cout << f.name << " ";
            }
        }
        std::cout << "\n";
    }
    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}
