// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 7.
Do exercise 6, but with three string values. So, if the user enters
the values Steinbeck, Hemingway, Fitzgerald, the output should be
Fitzgerald, Hemingway, Steinbeck.
*/

#include "section3.h"

int main()
{
    using namespace std;

    cout << "Enter 3 words and output will place in alphabetic order.\n\n";
    cout << "Enter three words:\n";

    string min;
    string mid;
    string max;

    decltype( min ) val{};

    for( std::size_t i{}; i < 3 && cin >> val; ++i )
    {
        decltype( min ) temp{};

        if( val < min || min.empty() )
        {
            temp = min;
            min = val;
            val = mid;
            mid = temp;
            max = val;
        }
        else if( val < mid || mid.empty() )
        {
            temp = mid;
            mid = val;
            max = temp;
        }
        else
        {
            max = val;
        }
    }

    if( !( cin ) )
    {
        simple_error( "Invalid entry" );
    }

    cout << std::format( "{}, {}, {}\n\n", min, mid, max );

    // Why is a string starting with an upper case always less than a string starting with a lower case?
    // hint below
    string word1 = "Zero";
    string word2 = "two";
    if( word1 <= word2 )
    {
        cout << "okay\n";
    }
    else
    {
        cout << "why not\n";
    }
    cout << std::format( "{}({}) {}({})\n", word1[0], static_cast<int>(word1[0]), word2[0], static_cast<int>( word2[0] ) );


    keep_window_open();
    return 0;
}
