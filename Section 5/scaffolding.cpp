//written by Jtaim
//date 27 Oct 2015
//updated 18 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Add comments here

*/

#include "section5.h"

int main()
try 
{
	/*<<your code here>>*/
	keep_window_open();
	return 0;
}
catch (std::exception& e) 
{
	std::cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) 
{
	std::cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
