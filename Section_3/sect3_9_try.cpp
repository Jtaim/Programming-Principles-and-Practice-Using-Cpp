//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.9 try this exercise
*/

#include "section3.h"

//exit EOF or ctrl-z
int main()
{
    // In simple programs this using statement is ok but never use in a header file and be careful in larger projects. you have been warned!
    using namespace std;

    double d{};
    cout << "Shows how C++ implicitly converts types. EOF to exit\n";
    while( cin >> d )
    {
        int i = d;	// conversion from 'double' to 'int', possible loss of data
        int j{ static_cast<int>( d ) };   // the {} enforces error narrowing conversion for possible loss of data and will get a compiler error
        char c = i; // conversion from 'int' to 'char', possible loss of data
        int i2 = c; // OK, all char values can fit into an int
        cout << format( "the entered double value: {}\n", d );
        cout << format( "double converted to int: {}\n", i );
        cout << format( "int converted to char: {}\n", c );
        cout << format( "char converted to int: {}\n", i2 );
    }

    keep_window_open();
    return 0;
}
