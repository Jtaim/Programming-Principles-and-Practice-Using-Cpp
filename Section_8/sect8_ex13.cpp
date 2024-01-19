/*
    Written by Jtaim
    Date 12 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 13
    - Write a function with input vector<string> argument.
    - returns a vector<int> containing the number of characters in each string.
    - also find the longest and shortest string.
    - lexicographically first and last string

    keep as one function and separate function?
    I guess depends on the situation but keeping 2 separate functions helps keeps each specialized.
    Could also just find size of each to find shortest and longest word.
    also for the lexicographically first and last string could use the sort function from the STL algorithm library
*/

#include"../includes/ppp.hpp"

template<typename T>
void print_vector( const std::vector<T>& v )
{
    if( !v.empty() )
    {
        for( const auto& element : v )
        {
            std::cout << element << '\n';
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "vector is empty\n";
    }
}

std::vector<int> find_size( const std::vector<std::string>& vs )
{
    std::vector<int> vn;
    if( !vs.empty() )
    {
        for( const auto& s : vs )
        {
            vn.push_back( static_cast<int>( s.size() ) );
        }
    }
    return std::move( vn );
}

int main()
{
    std::vector<std::string> vs{ "one hundred", "zero", "one", "five thousand", "two", "ZERO", "three", "four" };

    print_vector( vs );
    print_vector( find_size( vs ) );

    std::vector<std::string> lengths = vs;
    std::stable_sort( lengths.begin(), lengths.end(),
                      []( const std::string& a, const std::string& b ) { return a.size() < b.size(); } );
    print_vector( lengths );

    ppp::keep_window_open();
    return 0;
}
