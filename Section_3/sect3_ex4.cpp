// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3 exercise 4.
A program that prompts the user to enter two integer values.
Store these values in int variables named val1 and val2.
*/

#include "section3.hpp"

int main()
{
    using namespace std;

    cout << "Enter two integer values:\n";
    int val1{};
    int val2{};

    if( !( cin >> val1 >> val2 ) )
    {
        simple_error( "Invalid entry!" );
    }

    if( val1 < val2 )
    {
        cout << std::format( "{} < {}\n", val1, val2 );
    }
    else if( val1 > val2 )
    {
        cout << std::format( "{} > {}\n", val1, val2 );
    }
    else
    {
        cout << std::format( "{} == {}\n", val1, val2 );
    }

    cout << std::format( "{} + {} = {}\n", val1, val2, val1 + val2 );
    cout << std::format( "{} - {} = {}\n", val1, val2, val1 - val2 );
    cout << std::format( "{} * {} = {}\n", val1, val2, val1 * val2 );
    if( val2 == 0 )
    {
        simple_error( "I don't divide by zero" );
    }
    else
    {
        cout << std::format( "{} / {} = {}\n", val1, val2, static_cast<double>( val1 ) / static_cast<double>( val2 ) );
    }

    keep_window_open();
    return 0;
}
