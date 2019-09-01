//written by Jtaim
//date 6 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
section 5 exercise 7.
build upon section 4 exercise 18.
Write a program to solve quadratic equations(ax^2+bx+c=0).
x = (-b +/- sqrt(b^2-4ac))/2a
Check that b^2-4ac is not less than 0.
Write a function that print out the roots of a quadratic equation, given a,b,c.
If no real roots print out a message.
*/

#include "section5.h"

void quadratic(const double a, const double b, const double c)
{
	if(a == 0.0){
		error("a = 0; so can not derive any roots\n");
	} else if(c == 0.0){
		std::cout << "x = 0\n";
		std::cout << "x = " << -1.0 * b / a << std::endl;
	} else{
		auto sq{b * b - 4.0 * a * c};
		if(sq >= 0.0){
			std::cout << "x = " << (-1.0 * b + sqrt(sq)) / (2.0 * a) << std::endl;
			std::cout << "x = " << (-1.0 * b - sqrt(sq)) / (2.0 * a) << std::endl;
		} else{
			std::cout << "x = (" << -1.0 * b << " +i" << sqrt(fabs(sq)) << ")/" << (2.0 * a) << std::endl;
			std::cout << "x = (" << -1.0 * b << " -i" << sqrt(fabs(sq)) << ")/" << (2.0 * a) << std::endl;
		}
	}
}

int main()
try{
	std::cout << "Enter the a, b and c variables to solve the quadratic equation:\n";
	double a{};
	double b{1.0};
	double c{};
	if(!(std::cin >> a >> b >> c)){
		error("a non-numeric number entered.");
	}

	quadratic(a, b, c);

	keep_window_open();
	return 0;
}
catch(std::exception& e){
	std::cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
