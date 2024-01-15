//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/**
 * Section 3 Drill. This drill is to write a program that produces a
 * simple form letter based on user input.
 */

#include "section3.hpp"

int main()
{
    constexpr unsigned minAge{ 0 };
    constexpr unsigned maxAge{ 110 };

    std::cout << "Enter the name of the person you want to write to:\n";
    std::string first_name;
    std::cin >> first_name;
    std::cout << std::format( "Dear {},\n", first_name );

    std::cout << "\tHow are you? I am fine. I'm writing a simple program in C++\n";

    std::cout << "Enter a friends name:\n";
    std::cin >> first_name;
    std::cout << std::format( "Have you seen {} lately?\n", first_name );

    std::cout << "What is your friends gender? (Enter m for male and f for female)\n";
    unsigned char gender{};
    //check for correct entry
    while( std::cin >> gender )
    {
        gender = static_cast<unsigned char>( std::tolower( gender ) );
        if( gender == 'm' || gender == 'f' )
        {
            std::cout << std::format( "If you see {} ask {} to call me.\n", first_name, ( ( gender == 'm' ) ? "him" : "her" ) );
            break;
        }
        std::cout << std::format( "unrecognized gender selection ({}), please reenter: ", static_cast<char>( gender ) );
    }

    std::cout << "How old are you?\n";
    int age{};
    //check for valid age and valid cin to int
    if( std::cin >> age && age > minAge && age < maxAge )
    {
        std::cout << std::format( "I hear you just had a birthday and you are {} years old.\n", age );
        if( age < 12 )
        {
            std::cout << std::format( "Next year you will be {}.\n", age + 1 );
        }
        else if( age == 17 )
        {
            std::cout << "Next year you will be able to vote.\n";
        }
        else if( age > 70 )
        {
            std::cout << "I hope you are enjoying retirement.\n";
        }
        std::cout << "Yours sincerely,\n\nJ\n";
    }
    else
    {
        simple_error( "you're kidding!" );
    }

    keep_window_open();
    return 0;
}
