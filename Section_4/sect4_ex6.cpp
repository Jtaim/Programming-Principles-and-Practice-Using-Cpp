//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 6.
Make a vector holding the ten string values "zero", "one", . . . "nine".
Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output seven.
Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input seven gives the output 7.
*/

#include "section4.hpp"

int main()
{
    const std::vector<std::string_view> spelledNumbers{
      "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    std::cout << "Enter a number between 0 and 9 either spelled out or as the number.\n";

    std::string number;
    if( std::cin >> number && number.size() == 1 && std::isdigit( static_cast<unsigned char>( number[0] ) ) )
    {
        auto num{ atoi(number.data())};
        std::cout << num << " == " << spelledNumbers[num] << "\n\n";
    }
    // check if number is spelled out
    else
    {
        // convert to lower
        std::for_each( number.begin(), number.end(), []( auto& c ) { c = static_cast<char>( tolower( static_cast<unsigned char>( c ) ) ); } );

        // check if has a spelled out number
        auto spelledIndex = std::find( spelledNumbers.begin(), spelledNumbers.end(), number );
        if( spelledIndex != spelledNumbers.end() )
        {
            std::cout << number << " == " << ( spelledIndex - spelledNumbers.begin() ) << "\n\n";
        }
        else
        {
            simple_error( std::format( "{} is undefined input", number ) );
        }
    }

    keep_window_open();
    return 0;
}
