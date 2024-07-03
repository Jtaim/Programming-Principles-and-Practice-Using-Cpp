/*
    Written by Jtaim
    Date 20 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 4
    Write a program called multi_input.cpp (sect11_ex4.cpp) that prompts the user to enter several integers
    in any combination of octal, decimal, or hexadecimal, using the 0 and 0x base suffixes;
    interprets the numbers correctly; and converts them to decimal form.
    Then your program should output the values in properly spaced columns.
*/

#include "ppp.hpp"

int main()
try
{
    std::cout << "Enter several integers in any combination of "
        << "octal, decimal, or hexadecimal, using the 0 and 0x base suffixes.\n";
    std::ostringstream oss;
    std::cin.exceptions( std::cin.exceptions() | std::ios::badbit );
    for( std::string str_num; std::cin >> str_num; )
    {
        std::string base_name;
        auto base_flag{ std::dec };
        bool is_valid{ true };

        if( str_num.find( "0x" ) == 0 )
        {
            for( unsigned char c : str_num.substr( 2 ) )
            {
                if( !isxdigit( c ) )
                {
                    is_valid = false;
                    break;
                }
            }
            base_flag = std::hex;
            base_name = "hexadecimal";
        }
        else if( str_num.find( "0" ) == 0 )
        {
            for( char c : str_num.substr( 1 ) )
            {
                if( c < '0' || c > '7' )
                {
                    is_valid = false;
                    break;
                }
            }
            base_flag = std::oct;
            base_name = "octal";
        }
        else
        {
            for( unsigned char c : str_num )
            {
                if( !isdigit( c ) )
                {
                    is_valid = false;
                    break;
                }
            }
            base_flag = std::dec;
            base_name = "decimal";
        }

        if( is_valid )
        {
            std::istringstream iss{ str_num };
            iss.exceptions( iss.exceptions() | std::ios::badbit );
            int number{};
            iss >> base_flag >> number;
            std::print( oss, "{:8}{:12}converts to {} decimal\n", str_num, base_name, number );
        }
        else
        {
            std::print( oss, "{:8}is an invalid {} number!\n", str_num, base_name );
        }
    }

    std::cout << oss.str();

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
