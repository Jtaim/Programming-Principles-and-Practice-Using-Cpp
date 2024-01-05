//written by Jtaim
//date 6 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 6
Celsius to Fahrenheit converter
Fahrenheit to Celsius converter
*/

#include "section5.h"

// converts Celsius to Fahrenheit
// throws an exception if input is below -273.15C
static double ctof( double c )
{
    if( c < -273.15 )
    {
        error( "Can not be below absolute zero!\n" );
    }
    double c_to_f{ 9.0 / 5.0 * c + 32.0 };
    return c_to_f;
}

// converts Fahrenheit to Celsius
// throws an exception if input is below -459.67F
static double ftoc( double f )
{
    if( f < -459.67 )
    {
        error( "Can not be below absolute zero!\n" );
    }
    double f_to_c{ 5.0 / 9.0 * ( f - 32.0 ) };
    return f_to_c;
}

int main()
try
{
    std::cout << "Enter a temperature and unit of temperature (c = Celsius, f = Fahrenheit)\n";

    // get measurement
    double temperature{};
    if( !( std::cin >> temperature ) )
    {
        error( "entered non-numeric temperature." );
    }

    // get unit
    char unit{};
    std::cin >> unit;
    unit = narrow_cast<char, int>( tolower( static_cast<unsigned char>( unit ) ) );

    // convert temperatures
    switch( unit )
    {
        case 'c':
            temperature = ctof( temperature );
            unit = 'f';
            break;
        case 'f':
            temperature = ftoc( temperature );
            unit = 'c';
            break;
        default:
            error( "Unknown unit of measure for temperature." );
    }

    std::cout << "Converted temperature is " << temperature << unit << std::endl;

    keep_window_open();
    return 0;
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
