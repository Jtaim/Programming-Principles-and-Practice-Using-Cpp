/*
    Written by Jtaim
    Date 7 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 11
    Write a function that finds the smallest and the largest element of a vector argument and also computes the mean and the median.
    Do not use global variables.
    Either return a struct containing the results or pass them back through reference arguments.
    Which of the two ways of returning several result values do you prefer and why?
    pass result values by reference,  seems to lesson copy of data.
*/

#include"../includes/ppp.hpp"

template <typename T>
struct slmm_struct
{
    slmm_struct() = default;
    T small{};
    T large{};
    T mean{};
    T median{};
};

template <typename T>
void slmm( std::vector<T>& v, slmm_struct<T>& slmm)
{
    constexpr bool check =
        std::is_floating_point<T>::value ||
        std::is_same<short, T>::value ||
        std::is_same<unsigned short, T>::value ||
        std::is_same<int, T>::value ||
        std::is_same<unsigned int, T>::value ||
        std::is_same<long, T>::value ||
        std::is_same<unsigned long, T>::value ||
        std::is_same<long long, T>::value ||
        std::is_same<unsigned long long, T>::value;
    static_assert( check, "Vector must be of numeric type" );

    if( v.empty() )
    {
        ppp::error( "Vector is empty!" );
    }
    if constexpr( check )
    {
        slmm.small = slmm.large = v.front();
        for( auto elem : v )
        {
            if( slmm.large < elem )
            {
                slmm.large = elem;
            }
            if( slmm.small > elem )
            {
                slmm.small = elem;
            }
            slmm.mean += elem;
        }
        slmm.mean /= ppp::narrow_cast<T>( v.size() );
        // If n is odd then Median (M) = value of ((n + 1)/2)th item term.
        // If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
        sort( v.begin(), v.end() );	// sort numbers
        if( ( v.size() % 2 ) > 0 )
        {
            slmm.median = v.at( v.size() / 2 );
        }
        else
        {
            // if have even amount, remember vector index starts at zero
            // get 2 middle indexes and divide by 2
            slmm.median = ( v.at( v.size() / 2 - 1 ) + v.at( v.size() / 2 ) ) / 2;
        }
    }
}

int main()
try
{
    std::vector<double> dprice{ 3.99, 4.5, 3.45, 5.01, 6.23, 0.99 };
    slmm_struct<double> dinfo;
    slmm( dprice, dinfo );
    std::cout << "Largest price: " << dinfo.large << std::endl;
    std::cout << "Smallest price: " << dinfo.small << std::endl;
    std::cout << "Mean price: " << dinfo.mean << std::endl;
    std::cout << "Median price: " << dinfo.median << std::endl;
    std::cout << "\n\n";

    std::vector<int> nprice{ 3, 4, 2, 5, 6, 1 };
    slmm_struct<int> ninfo;
    slmm( nprice, ninfo );
    std::cout << "Largest price: " << ninfo.large << std::endl;
    std::cout << "Smallest price: " << ninfo.small << std::endl;
    std::cout << "Mean price: " << ninfo.mean << std::endl;
    std::cout << "Median price: " << ninfo.median << std::endl;

    ppp::keep_window_open();
    return 0;
}
catch( std::exception& e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}