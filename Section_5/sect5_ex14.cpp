//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 14
Read (day-of-the-week,value) pairs from standard input.
Collect all the values for each day of the week in a vector<int>.
Write out the values of the seven day-of-the-week vectors.
Print out the sum of the values
Ignore illegal days, but accept common synonyms.
escape by "quit" for day value entry
print number of rejected entries.

Tuesday 23 Friday 56 Tuesday –3 Thursday 24 Funday 12 mon 3
*/

#include "section5.h"

using pType = std::pair<std::string, int>;
using vType = std::vector<pType>;
using valueType = pType::second_type;

/*	addition function.
  Inputs:		two numbers
  outputs:	    valid resulting number
  Errors:		element overflow
*/
[[nodiscard]] static valueType add( valueType n1, valueType n2 )
{
    if( ( ( n2 > 0 ) && ( n1 > ( std::numeric_limits< valueType>::max() - n2 ) ) ) ||
        ( ( n2 < 0 ) && ( n1 < ( std::numeric_limits< valueType>::min() - n2 ) ) ) )
    {
        error( "overflow error" );
    }
    return n1 + n2;
}

int main()
try
{
    constexpr std::array weekdays
    {
        std::array{ "sun","sunday"    },
        std::array{ "mon","monday"    },
        std::array{ "tue","tuesday"   },
        std::array{ "wed","wednesday" },
        std::array{ "thu","thursday"  },
        std::array{ "fri","friday"    },
        std::array{ "sat","saturday"  },
    };

    constexpr std::string_view termination{ "quit" };

    std::cout << "Enter a day of the week (ex:Mon or Monday) and a value. Enter " << termination << " to exit\n";
    unsigned rejects{};
    vType day_value_pairs;
    std::string q{};
    while( q != termination )
    {
        pType day_value_pair;
        std::cin >> day_value_pair.first;
        if( !std::cin.good() || day_value_pair.first == termination )
        {
            if( std::cin.eof() || day_value_pair.first == termination ) break;
            else error( "input failure" );
        }
        std::for_each( day_value_pair.first.begin(), day_value_pair.first.end(),
                       []( auto& c ) { c = narrow_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) ); } );

        // check for matching day
        auto valid_day = std::find_if( weekdays.begin(), weekdays.end(), [&day_value_pair]( const auto& wd )
        {
            return std::find( wd.begin(), wd.end(), day_value_pair.first ) != wd.end();
        } );

        // check if valid weekday was found?
        bool good_day = valid_day != weekdays.end();
        if( !good_day )
        {
            ++rejects;
        }
        else
        {
            day_value_pair.first = valid_day->back();
        }

        // check if valid weekday value was found?
        std::cin >> day_value_pair.second;
        if( !std::cin.good() )
        {
            // Visual Studio detects an overflow with a failed input flag and leaves the space or new line character in the buffer. 
            std::cin.clear();
            char c{};
            std::cin.get( c );
            if( c == ' ' || c == '\n' )
            {
                error( "overflow input integer!" );
            }
            else
            {
                error( "entered invalid day data value" );
            }
        }
        if( good_day ) day_value_pairs.push_back( day_value_pair );
    }

    //print the results
    valueType sum{};
    for( auto p : day_value_pairs )
    {
        sum = add( sum, p.second );
        p.first[0] = static_cast<char>( std::toupper( static_cast<unsigned char>( p.first[0] ) ) );
        std::cout << std::format( "{} has data of{}.\n", p.first, p.second );
    }
    std::cout << "The total sum of the data is " << sum << std::endl;
    std::cout << "\n\n" << std::left << std::setfill( '.' ) << std::setw( 20 ) << "rejects" << " " << rejects << std::endl;

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
