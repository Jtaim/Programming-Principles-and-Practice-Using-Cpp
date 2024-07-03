/*
    Written by Jtaim
    Date 20 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 3
    Write a program that removes all vowels from a file (“disemvowels”).
    For example, Once upon a time! becomes nc pn tm!.
*/

#include "ppp.hpp"

// return the non vowel character 
static std::optional<char> disemvowel( char c )
{
    constexpr std::array vowels{ 'a','e','i','o','u' };
    c = static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) );
    if( vowels.cend() == std::find( vowels.begin(), vowels.end(), c ) )
    {
        return c;
    }
    return std::nullopt;
}

int main()
try
{
    constexpr auto space{ '\x20' };
    constexpr std::array vowels{ 'a','e','i','o','u' };
    constexpr std::string_view example_string{ "Once upon a time!" };

    std::istringstream os{ example_string.data() };

    for( char c{}, temp{}; os.get( c ); )
    {
        if( temp == space && c == space ) continue;  // eat duplicate spaces
        if(disemvowel(c))
        {
            std::cout << c;
            temp = c;
        }
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
