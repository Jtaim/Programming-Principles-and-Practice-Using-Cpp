//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 16.
A program that finds the mode of a set of positive integers
The "mode" is the value that occurs most often.
If no number is repeated, then there is no mode for the list.
Refer to drill 3
*/

#include "section4.h"

int main()
{
    using vType = std::vector<int>;
    std::cout << "Enter a sequence of positive numbers to find the MODE. (enter any non numeric to indicate last number)\n";

    vType sequence;  // vector to hold input sequence
    do
    {
        vType::value_type number{};
        if( !( std::cin >> number ) )
        {
            break;
        }
        else if( number >= 0 )
        {
            sequence.push_back( number );
            continue;
        }
        else
        {
            simple_error( std::format( "{} is less than zero", number ) );
        }
    } while( true );

    if( sequence.empty() )
    {
        std::cout << "nothing entered\n";
    }
    else
    {
        std::sort( sequence.begin(), sequence.end() );
        vType::value_type mode{};
        vType::difference_type count{};

        // search sorted vector for most duplicates
        for( auto i{ sequence.cbegin() }, next{ sequence.cbegin() }; i != sequence.end(); i = next )
        {
            // find_if_not searches for an element for which the predicate returns false.
            next = std::find_if_not( i, sequence.cend(), [i]( auto comp ) { return *i == comp; } );
            auto temp_count{ next - i };
            if( temp_count >= count )
            {
                count = temp_count;
                mode = *i;
            }
        }

        // print out the MODE
        if( count > 1 )
        {
            std::cout << std::format( "The MODE of entered sequence is {0}.\nThe number {0} was found {1} times.\n", mode, count );
        }
        else
        {
            std::cout << "There is no MODE from this set.\n";
        }
    }

    keep_window_open();
    return 0;
}
