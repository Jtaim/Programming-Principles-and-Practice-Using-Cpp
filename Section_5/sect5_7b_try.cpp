//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.7 part 2
build and test the program from the section.
Does it provide the correct results?
What is the least amount of input you can give it to get it to fail?
*/

#include "section5.hpp"

int main()
{
    constexpr double min_temp{ -150.0 };
    constexpr double max_temp{ 150.0 };
    try
    {
        std::cout << "Enters some temperatures in Fahrenheit.\n";
        std::vector<double>temps;
        for( double temp{}; std::cin >> temp;)
        {
            if( temp < min_temp || temp > max_temp )
            {
                error( std::format( "{} exceeds the maximum or minimum temperature extremes", temp ) );
            }
            temps.push_back( temp );
        }

        // check for empty vector
        if( temps.size() != 0 )
        {
            std::sort( temps.begin(), temps.end() );
            auto sum = std::accumulate( temps.begin(), temps.end(), 0.0 );
            std::cout << "High temperature: " << temps.back() << std::endl;
            std::cout << "Low temperature: " << temps.front() << std::endl;
            std::cout << "Average temperature: " << sum / temps.size() << std::endl;
        }
        else
        {
            std::cout << "No temperatures entered.\n";
        }

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
}
