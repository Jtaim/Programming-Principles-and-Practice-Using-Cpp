//written by Jtaim
//date 23 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.4 try this exercise
*/

#include "section3.hpp"	//custom header

int main()
{
    using namespace std;

    cout << "Please enter a value: ";
    int n;
    cin >> n;

    cout << format( "n == {} \nn + 1 == {} \nthree * n == {} \ntwice n == {} \nn squared == {} \nhalf of n == {} \nsquare root of n == {} \n",
                    n, n + 1, n * 3, n + n, n * n, n / 2.0, std::sqrt( n ) );

    keep_window_open();
    return 0;
}
