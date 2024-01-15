//written by Jtaim
//date 26 Mar 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.2.1
The character 'b' is char('a'+1), 'c' is char('a'+2), etc.
Use a loop to write out a table of characters with their corresponding integer values:
a     97
b     98
. . .
z     122
*/

#include "section4.hpp"

int main()
{
    // 97 = 'a' lower case letters 122 = 'z'
    unsigned char character{ 'a' };
    while( character <= 'z' )
    {
        std::cout << std::format( "'{0}' = {0:<3d}    '{1}' = {1:<3d}\n",
                                  static_cast<char>( character ), static_cast<char>( std::toupper( character ) ) );
        ++character;
    }

    keep_window_open();
    return 0;
}
