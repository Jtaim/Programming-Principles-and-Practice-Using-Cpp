//written by Jtaim
//date 19 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.3.1
compile the error examples from this section and see how the compiler responds.
*/

#include "section5.h"

int area( int length, int width );

int main()
{
    //int s1 = area(7;
    //error was expected a ')'
    //fix 
    int s1 = area( 7, 2 );

    //int s2 = area(7)
    //error was too few arguments in function call
    //expected a ';'
    //fix
    int s2 = area( 7, 2 );

    //Int s3 = area(7)
    //error was identifier "Int" is undefined
    //too few arguments in function call
    //expected a ';'
    //fix
    int s3 = area( 7, 2 );

    //int s4 = area('7);
    //error was has opening quote int for some reason
    //too few arguments in function call
    //fix
    int s4 = area( 7, 2 );
}

// another error is when linking is that function declaration was missing a definition
// I added a definition below
int area( int length, int width )
{
    return length * width;
}
