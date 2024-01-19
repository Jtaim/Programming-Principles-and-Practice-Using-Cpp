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
*/

#include "../includes/ppp.hpp"

// print name age pair value vectors, with label
void print( const std::string& label, const std::vector<std::string>& names, const std::vector<double>& ages )
{
    std::cout << label << '\n';
    if( names.size() == ages.size() )
    {
        for( std::size_t index{}; index < names.size(); ++index )
        {
            std::cout << std::format( "{} is {} years old\n", names.at( index ), ages.at( index ) );
        }
    }
}

// get ages for a given vector of names
std::vector<double> get_age( const std::vector<std::string>& names )
{
    std::vector<double> ages;
    for( auto& name : names )
    {
        std::cout << "Enter age for " << name << " ";
        double age{};
        while( !( std::cin >> age ) )
        {
            std::cin.clear();
            std::cin.ignore( std::cin.rdbuf()->in_avail() );	//clear cin buffer
            std::cout << "Invalid age entered! Try again.\n";
        }
        ages.push_back( age );
    }
    return std::move( ages );
}

// sort names and ages to the sorted names
void sort( std::vector<std::string>& names, std::vector<double>& ages )
{
    if( !names.empty() && ( names.size() == ages.size() ) )
    {
        for( std::size_t idx1{}; idx1 < names.size(); ++idx1 )                  // name to compare
        {
            for( std::size_t idx2{ idx1 + 1 }; idx2 < names.size(); ++idx2 )    // compare with rest of names
            {
                if( names.at( idx1 ) > names.at( idx2 ) )                       // sort from lowest to highest
                {
                    // store greater element
                    std::string temp_name = std::move( names.at( idx1 ) );
                    double temp_age = ages.at( idx1 );
                    // place lesser element at previous greater element
                    names.at( idx1 ) = names.at( idx2 );
                    ages.at( idx1 ) = ages.at( idx2 );
                    // place greater in the previous lesser element
                    names.at( idx2 ) = std::move( temp_name );
                    ages.at( idx2 ) = temp_age;
                }
            }
        }
    }
}

int main()
{
    std::vector<std::string> names{ "James","Tina","Alex","Ivan","Michelle" };
    auto ages{ get_age( names ) };

    std::cout << "\n\n";
    print( "As entered name and age pair", names, ages );

    sort( names, ages );

    std::cout << "\n\n";
    print( "Sorted name and age pair", names, ages );

    ppp::keep_window_open();
    return 0;
}
