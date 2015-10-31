//written by Jtaim
//date 27 Oct 2015
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
catch (exception& e) 
{
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) 
{
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}