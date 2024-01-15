//written by Jtaim
//date 19 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.3.2
compile the error examples from this section and see how the compiler responds.
*/

#include "section5.hpp"

int area( int length, int width );

int main()
{
    //int x0 = arena(7);
    // error is identifier "arena" is undefined

    //int x1 = area(7);
    // error is too few arguments in function call

    //int x2 = area("seven", 2);
    // error is argument of type "const char *" is incompatible with parameter of type "int"

    //int x3 = area(1, 2, 3);
    // error is too many arguments in function call
}
