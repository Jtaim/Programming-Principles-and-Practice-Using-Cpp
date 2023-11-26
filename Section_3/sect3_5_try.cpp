//written by Jtaim
//date 23 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3.5 try this exercise
*/

#include "section3.h" //custom header
#include <algorithm>

int main()
{
    std::cout << "A program to check for repeating words. EOF or ctrl-z to exit\n";
    std::cout << "Enter a sentence to check: ";

    std::string previous;
    std::string current;
    unsigned wordCount{};
    while( std::cin >> current )
    {
        ++wordCount;

        for( auto index{ current.begin() }; index < current.cend(); ++index )
        {
            // check for and remove punctuations
            if( std::ispunct( static_cast<unsigned char>( *index ) ) != 0 )
            {
                current.resize( index - current.begin() );
                break;
            }
            // make string lower case
            if( islower( static_cast<unsigned char>( *index ) ) == 0 )
            {
                *index = static_cast<char>( std::tolower( static_cast<unsigned char>( *index ) ) );
            }
        }

        if( !current.empty() && previous == current )
        {
            std::cout << std::format( "repeated word: {}\n", current );
        }

        previous = current;
    }

    std::cout << std::format( "Total words: {}\n", wordCount );

    keep_window_open();
    return 0;
}

// She she laughed He he He because what he did did not look very very good good.

