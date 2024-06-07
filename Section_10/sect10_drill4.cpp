/*
    Written by Jtaim
    Mar 24 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Drill 4
    Open an ofstream and output each point to a file named mydata.txt.
    On Windows, we suggest the .txt suffix to make it easier to look at the data with an ordinary text editor.
*/

#include "../includes/ppp.hpp"
#include "Point.hpp"

int main()
try
{
    constexpr size_t how_many{ 7 };
    using point_type = int;
    constexpr std::string_view point_file{ "mydata.txt" };

    std::cout << "Enter " << how_many << " ( x, y ) pairs:\n";
    std::vector<Point<point_type>> original_points( how_many, Point<point_type>() );
    std::ofstream fout{ point_file.data()};

    if( !fout )
    {
        ppp::error( "Can't open output file ", point_file.data() );
    }
    for( auto &p : original_points )
    {
        while( !( std::cin >> p ) )
        {
            if( std::cin.eof() )
            {
                ppp::error( "EOF found before filling required data" );
            }
            std::cout << "bad input try again\n";
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        fout << p;
    }
    fout.close();

    for( const auto &p : original_points )
    {
        std::cout << p << "\n";
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
