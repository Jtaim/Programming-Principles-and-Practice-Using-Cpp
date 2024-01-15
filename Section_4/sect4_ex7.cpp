//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 7.
Modify the "mini calculator from exercise 5 to accept (just) single-digit numbers written as either digits
or spelled out.
*/

#include "section4.hpp"

static double add( double arg1, double arg2 )
{
    return arg1 + arg2;
}

static double subtract( double arg1, double arg2 )
{
    return arg1 - arg2;
}

static double multiply( double arg1, double arg2 )
{
    return arg1 * arg2;
}

static double divide( double arg1, double arg2 )
{
    if( arg2 == 0 )
    {
        simple_error( "division by zero is not allowed.\n" );
    }
    return arg1 / arg2;
}

constexpr auto spelledNumbers = std::to_array<std::string_view>
( {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
  } );

static int getNumber()
{
    std::string input;
    int number{};
    if( std::cin >> input && input.size() == 1 && std::isdigit( static_cast<unsigned char>( input[0] ) ) )
    {
        number = atoi( input.data() );
    }
    // check if number is spelled out
    else
    {
        // convert to lower
        std::for_each( input.begin(), input.end(), []( auto& c ) { c = static_cast<char>( tolower( static_cast<unsigned char>( c ) ) ); } );

        // check if has a spelled out number
        auto spelledIndex = std::find( spelledNumbers.begin(), spelledNumbers.end(), input );
        if( spelledIndex != spelledNumbers.end() )
        {
            number = static_cast<int>(spelledIndex - spelledNumbers.begin());
        }
        else
        {
            simple_error( std::format( "{} is an undefined input", input ) );
        }
    }
    return number;
}

using math = double( * )( double, double ); // function pointer type
constexpr auto calculate = std::to_array<std::pair<char, math>>
( {
  {'+', add},
  {'-', subtract},
  {'*', multiply},
  {'/', divide}
  } );

int main()
{
    std::cout << "Enter 2 numbers and an operation (+, -, *, /).\n";
    std::cout << "Number entered must be between 0 and 9 either spelled out or as the number.\n\n";

    double arg1{ static_cast<double>(getNumber()) };
    double arg2{ static_cast<double>(getNumber()) };

    char op{};
    std::cin >> op;
    auto itr{ std::find_if( calculate.begin(), calculate.end(), [op]( const auto& c ) { return c.first == op; } ) };
    if( itr == calculate.end() )
    {
        simple_error( std::format( "{} is an undefined operator", op ) );
    }
    std::cout << std::format( "{} {} {} = {}", arg1, op, arg2, itr->second( arg1, arg2 ) ) << std::endl;

    keep_window_open();
    return 0;
}
