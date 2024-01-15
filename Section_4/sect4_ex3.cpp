//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 3.
Read a sequence of double values into a vector.
Think of each value as the distance between two cities along a given route.
Compute and print the total distance (the sum of all distances).
Find and print the smallest and greatest distance between two neighboring cities.
Find and print the mean distance between two neighboring cities.
*/

#include "section4.hpp"

int main()
{
    std::vector<double> distances;

    std::cout << "Please enter a sequence of numbers (representing distances).\n";

    for( double distance{}; std::cin >> distance; )
    {
        distances.push_back( distance );
    }

    std::string output;
    if( distances.empty() )
    {
        output = std::format( "no distances entered\n" );
    }
    else
    {
        auto sum{ std::accumulate( distances.begin(), distances.end(), 0.0 ) };
        output = std::format( "The total distance: {}\n", sum );
        std::sort( distances.begin(), distances.end() );
        output = std::format( "{}The smallest distance: {}\n", output, distances.front() );
        output = std::format( "{}The greatest distance: {}\n", output, distances.back() );
        output = std::format( "{}The mean distance: {}\n", output, sum / distances.size() );
    }
    std::cout << output << std::endl;

    keep_window_open();
    return 0;
}
