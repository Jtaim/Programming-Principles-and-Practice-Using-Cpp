/*
    Written by Jtaim
    Mar 24 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Drill 2
    Using the code and discussion in Section 10.4, prompt the user to input seven (x,y) pairs.
    As the data is entered, store it in a vector of Points called original_points.
*/

#include "../includes/ppp.hpp"
#include "Point.hpp"

int main()
try
{
    constexpr size_t how_many{ 7 };
    using point_type = int;

    std::cout << "Enter " << how_many << " ( x, y ) pairs:\n";
    std::vector<Point<point_type>> original_points(how_many, Point<point_type>() );

    for( auto& p : original_points )
    {
        while( !( std::cin >> p ) )
        {
            if( std::cin.eof() )
            {
                ppp::error( "EOF found before filling required data" );
            }
            std::cout << "bad input try again\n";
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception& e )
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