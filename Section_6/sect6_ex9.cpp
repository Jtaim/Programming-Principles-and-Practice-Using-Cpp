//Written by Jtaim
//Date 2 Dec 2015
//updated 28 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 9
read digits and compose them into integers. For example, 123 is read as the characters 1, 2, and 3.
Output of 123 is 1 hundred and 2 tens and 3 ones.
The numbers is output as int value.
Handle up to 4 digits.
terminate program with '|'.
*/

#include "section6.h"

int main()
{
    constexpr auto denomination = std::to_array<std::string_view>( { "one", "ten", "hundred", "thousand" } );

    try
    {

        std::cout << std::format("Enter a number up to digits long.\n", denomination.size());
        std::string digits;
        std::cin >> digits;

        if( digits.size() > denomination.size() || digits.empty() )
        {
            error( "input is empty or larger than know denomination" );
        }

        std::cout << digits << " is ";
        // step through the digits marking their denomination
        for( auto itr = digits.cbegin(); itr != digits.cend(); ++itr )
        {
            if( !isdigit( static_cast<unsigned char>( *itr ) ) )
            {
                error( "found a non number character" );
            }

            // get starting denomination iterator
            // to find the denomination we must work backwards through the array
            // sense digits can vary we find digit max denomination size
            auto i = denomination.begin() + digits.size() - 1;

            // now let for loop step it down the denomination array
            i -= ( itr - digits.begin() );

            // out to console with formating
            std::cout << std::format("{} {}{}{}", *itr, *i, ( *itr != '1' ? "s" : "" ), ( itr + 1 != digits.cend() ? " and " : ".\n" ));
        }
    }
    catch( std::exception& e )
    {
        std::cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch( ... )
    {
        std::cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }

    keep_window_open();
    return 0;
}
