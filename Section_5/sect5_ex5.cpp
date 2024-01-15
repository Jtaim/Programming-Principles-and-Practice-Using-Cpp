//written by Jtaim
//date 5 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 5
Celsius to Kelvin converter
Added Kelvin to Celsius converter
*/
#include "section5.hpp"

// converts Celsius to Kelvin
// throws an exception if input is below -273.15C
static double ctok( double c )
{
    if( c < -273.15 )
    {
        error( "Can not be below absolute zero!" );
    }
    constexpr double conversion_constant{ 273.15 };
    double c_to_k{ c + conversion_constant };
    return c_to_k;
}

// converts Kelvin to Celsius
// throws an exception if input is below 0k
static double ktoc( double k )
{
    if( k < 0 )
    {
        error( "Can not be below absolute zero!" );
    }
    constexpr double conversion_constant{ 273.15 };
    double k_to_c{ k - conversion_constant };
    return k_to_c;
}

int main()
{
    try
    {
        std::cout << "Enter a temperature and unit of temperature (c = Celsius, k = Kelvin)\n";

        // get measurement
        double temperature{};
        if( !( std::cin >> temperature ) )
        {
            error( "entered non-numeric temperature." );
        }

        // get unit
        char unit{};
        std::cin >> unit;
        unit = narrow_cast<char, int>( tolower( static_cast<unsigned char>(unit) ) );

        // convert temperatures
        switch( unit )
        {
            case 'c':
                temperature = ctok( temperature );
                unit = 'k';
                break;
            case 'k':
                temperature = ktoc( temperature );
                unit = 'c';
                break;
            default:
                error( "Unknown unit of measure for temperature." );
        }

        std::cout << "Converted temperature is " << temperature << unit << std::endl;

        keep_window_open();
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
    return 0;
}
