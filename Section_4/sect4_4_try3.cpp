//written by Jtaim
//date 26 Mar 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.2.1
The character 'b' is char('a'+1), 'c' is char('a'+2), etc. Use a loop to write out a table of characters with their corresponding integer values:
a     97
b     98
. . .
z     122
*/

#include "section4.h"	//custom header

int main()
{
    using namespace std;
    int index{ 97 };	// 97 = 'a' lower case letters 122 = 'z'
    while (index <= 122) {
        cout << static_cast<char>(index) << "\t" << index << endl;
        ++index;
    }
    keep_window_open();
    return 0;
}
