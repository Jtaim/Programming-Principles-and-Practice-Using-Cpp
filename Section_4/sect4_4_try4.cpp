//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.2.3
The character 'b' is char('a'+1), 'c' is char('a'+2), etc.
Use a loop to write out a table of characters with their corresponding integer values:
a     97
b     98
. . .
z     122
*/

#include "section4.h"	//custom header

int main()
{
    for( unsigned char character{ 'a' }; character <= 'z'; ++character )
    {
        std::cout << std::format( "'{0}' = {0:<3d}    '{1}' = {1:<3d}\n",
                                  static_cast<char>( character ), static_cast<char>( std::toupper( character ) ) );
    }

    keep_window_open();
    return 0;
}
