//Written by Jtaim
//Date 15 Sept 2015
//Updated 1 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

// simple hello world program

#include<iostream>

//C++ programs start by executing the function main
//use std to used the standard library could also use using namespace std;
int main()
{
	std::cout << "Hello, World!\n"		//output "Hello, World!"
		<< "Here we go again.\n";
	std::cin.get();						//wait for a character to be entered
	return 0;
}
