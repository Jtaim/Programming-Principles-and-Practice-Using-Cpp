/*
    Written by Jtaim
    Date 22 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 7
    - Read 5 names into vector<string> name.
    - Prompt user for age of the people named.
    - Store the ages in a vector<double>.
    - Print the 5 name age pairs.
    - Sort the names.
    - Print the sorted 5 name age pairs.
    Section 8 Exercise 8
    - add ability to create variable number of names
*/

#include "../includes/ppp.hpp"

struct Name_Age
{
    Name_Age() = default;
    Name_Age( std::string n, double a ) : name{ n }, age{ a } {}
    std::string name;
    double age{};
};

// print name age pair value vector, with label
void print( const std::string& label, const std::vector<Name_Age>& na )
{
    std::cout << label << '\n';
    {
        for( auto& x : na )
        {
            std::cout << std::format( "{} is {} years old\n", x.name, x.age );
        }
    }
}

// get names and ages
std::vector<Name_Age> get_name_age()
{
    std::vector<Name_Age> na;
    while( true )
    {
        std::string name;
        double age{};
        std::cout << "Enter a name: ";
        std::cin >> name;
        if( name == "stop" )
        {
            break;
        }
        std::cout << "Enter age for " << name << ": ";
        while( !( std::cin >> age ) )
        {
            std::cin.clear();
            std::cin.ignore( std::cin.rdbuf()->in_avail() );	//clear cin buffer
            std::cout << "Invalid age entered! Try again.\n";
        }
        na.push_back( std::move( Name_Age{ name, age } ) );
    }
    return std::move( na );
}

int main()
{
    auto names_ages{ get_name_age() };

    std::cout << "\n\n";
    print( "As entered name and age pair", names_ages );

    std::sort( names_ages.begin(), names_ages.end(), []( Name_Age a, Name_Age b ) { return a.name < b.name; } );

    std::cout << "\n\n";
    print( "Sorted name and age pair", names_ages );

    ppp::keep_window_open();
    return 0;
}