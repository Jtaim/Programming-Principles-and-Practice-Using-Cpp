/*
    WRITTEN BY JTAIM
    DATE 19 SEPT 2019
    STROUSTRUP, BJARNE. PROGRAMMING: PRINCIPLES AND PRACTICE USING C++. PEARSON EDUCATION. KINDLE EDITION.

    SECTION 11 EXERCISE 1
    WRITE A PROGRAM THAT READS A TEXT FILE AND CONVERTS ITS INPUT TO ALL LOWER CASE, PRODUCING A NEW FILE.
*/

#include "ppp.hpp"

int main()
try
{
    std::ofstream ofs{ "sect11_ex1.txt" };
    std::ifstream ifs{ "sect11_ex1.cpp" };
    for( char c; ifs.get( c ); )
    {
        ofs << static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) );
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
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
