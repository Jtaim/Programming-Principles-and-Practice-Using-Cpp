//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.2.3
The character 'b' is char('a'+1), 'c' is char('a'+2), etc. Use a loop to write out a table of characters with their corresponding integer values:
a     97
b     98
. . .
z     122
*/

#include "section4.h"	//custom header

int main()
{
    using std::cout;
    for (int index = 97; index <= 122; ++index)	//do to narrowing conversion  to char limit index < 256
    {
        cout << static_cast<char>(index) << '\t' << index << '\t';					//lower case letters
        cout << static_cast<char>(index - 32) << '\t' << index - 32 << std::endl;	//upper case letters
    }
    keep_window_open();
    return 0;
}
