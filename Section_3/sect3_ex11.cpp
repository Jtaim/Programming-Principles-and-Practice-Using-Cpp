//written by Jtaim
//date 25 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 11.
a program that prompts the user to enter some number of pennies (1-cent coins),
nickels (5-cent coins), dimes (10-cent coins), quarters (25-cent coins),
half dollars (50-cent coins), and one-dollar coins (100-cent coins).
Query the user separately for the number of each size coin, e.g., “How many pennies do you have?”
Then your program should print out something like this:
You have 23 pennies.
You have 17 nickels.
You have 14 dimes.
You have 7 quarters.
You have 3 half dollars.
The value of all of your coins is 573 cents.
*/

#include "section3.hpp"

long long getInput()
{
    long long val{};
    if( !( std::cin >> val ) )
    {
        simple_error( "Invalid integer value\n" );
    }
    return val;
}

int main()
{
    using namespace std;

    cout << "Lets count some change $$$$!\n";

    cout << "Enter number of pennies: ";
    auto penny = getInput();

    cout << "Enter number of nickels: ";
    auto nickel = getInput();

    cout << "Enter number of dimes: ";
    auto dime = getInput();

    cout << "Enter number of quarters: ";
    auto quarter = getInput();

    cout << "Enter number of half dollars: ";
    auto half_dollar = getInput();

    cout << "Enter number of dollar coins: ";
    auto dollar = getInput();

    string denomination;
    if( penny > 0 )
    {
        cout << std::format( "you have {} {}", penny, penny == 1 ? "penny" : "pennies" ) << endl;
    }

    if( nickel > 0 )
    {
        cout << std::format( "you have {} {}", nickel, nickel == 1 ? "nickel" : "nickels" ) << endl;
    }

    if( dime > 0 )
    {
        cout << std::format( "you have {} {}", dime, dime == 1 ? "dime" : "dimes" ) << endl;
    }

    if( quarter > 0 )
    {
        cout << std::format( "you have {} {}", quarter, quarter == 1 ? "quarter" : "quarters" ) << endl;
    }

    if( half_dollar > 0 )
    {
        cout << std::format( "you have {} {}", half_dollar, half_dollar == 1 ? "half dollar" : "half dollars" ) << endl;
    }

    if( dollar > 0 )
    {
        cout << std::format( "you have {} {}", dollar, dollar == 1 ? "dollar" : "dollars" ) << endl;
    }

    auto total = penny + nickel * 5 + dime * 10 + quarter * 25 + half_dollar * 50 + dollar * 100;
    cout << std::format( "your total is ${}", total / 100.0 ) << endl;

    keep_window_open();
    return 0;
}
