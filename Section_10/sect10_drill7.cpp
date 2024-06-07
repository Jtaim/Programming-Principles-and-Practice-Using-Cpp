/*
    Written by Jtaim
    Mar 24 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Drill 7
    Compare the two vectors and print Something's wrong! if the number of elements or the values of elements differ.
*/

#include "../includes/ppp.hpp"
#include "Point.hpp"

int main()
try
{
    constexpr size_t how_many{ 7 };
    using point_type = int;
    constexpr std::string_view point_file{ "mydata.txt" };

    std::cout << "Enter " << how_many << " (x,y) pairs:\n";
    std::vector<Point<point_type>> original_points;
    std::ofstream fout{ point_file.data() };

    if( !fout )
    {
        ppp::error( "Can't open output file ", point_file.data() );
    }
    for( size_t i{}; i < how_many; ++i )
    {
        decltype( original_points.begin() )::value_type p{};
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
        original_points.push_back( p );
        fout << p;
    }
    fout.close();

    // set a breakpoint here and modify the mydata.txt file to induce errors

    //processed_points;
    std::ifstream fin{ point_file.data() };
    if( !fin )
    {
        ppp::error( "Can't open input file ", point_file.data() );
    }
    std::vector<decltype( original_points.begin() )::value_type> processed_points;
    decltype( original_points.begin() )::value_type point{};
    while( fin >> point )
    {
        processed_points.push_back( point );
    }

    std::cout << "From user points:\n";
    for( const auto &po : original_points )
    {
        std::cout << po << "\n";
    }
    std::cout << "From file points:\n";
    for( const auto &pf : processed_points )
    {
        std::cout << pf << "\n";
    }

    if( original_points.size() == processed_points.size() )
    {
        auto p2 = processed_points.cbegin();
        for( const auto& p : original_points)
        {
            if( p != *p2 )
            {
                std::cout << "Point " << p << "is not equal to " << *p2;
                break;
            }
            ++p2;
        }
    }
    else
    {
        std::cout << "Point vector sizes are not equal";
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::cerr << R"(exception: )" << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << R"(exception)";
    ppp::keep_window_open();
    return 2;
}
