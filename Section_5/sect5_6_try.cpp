//written by Jtaim
//date 20 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.6
See what an uncaught exception error looks like using the error() function.
*/

#include "section5.h"

int main()
{
	error("so this is what an uncaught error looks like");
	// compile and run using gcc in command line and got following results
	// terminate called after throwing an instance of 'std::runtime_error'
	// what():  so this is what an uncaught error looks like
	// This application has requested the Runtime to terminate it in an unusual way.
	// Please contact the application's support team for more information.
}
