//written by Jtaim
//date 20 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.5
compile and test the program from this section.
*/

#include "section5.h"

//****************************************************************************
// calculate area of a rectangle
// error-condition: length or width are negative
// error-condition: result overflowed
int area(int length, int width)
{
	if(length <= 0 || width <= 0){
		std::cout << "area() condition <= 0 error\n";
		return 0;
	}
	int a = length * width;
	if(a <= 0){
		std::cout << "area() exceeded positive integer overflow error\n";
		return 0;
	}
	return a;
}
//****************************************************************************
// calculate area within frame
// calculate frame width;
// error-conditions: length or width are negative
int framed_area(int x, int y)
{
	constexpr int frame_width = 2;
	x -= frame_width;
	y -= frame_width;
	if(x <= 0 || y <= 0){
		std::cout << "frame_width() condition <= 0 error\n";
		return 0;
	}
	return area(x, y);
}
//*****************************************************************************
int main()
{
	int x = 200000;
	int y = 300000;
	int z = 500000;
	int area1 = area(x, y);
	std::cout << "area1 = " << area1 << std::endl;
	int area2 = framed_area(3, z);
	std::cout << "area2 = " << area2 << std::endl;
	int area3 = framed_area(y, z);
	std::cout << "area3 = " << area3 << std::endl;
	if(area3 == 0){
		std::cout << "div by 0 error\n";
	} else{
		double ratio = double(area1) / area3;        // convert to double to get
													 // floating-point division
		std::cout << "ratio = " << ratio << std::endl;
	}
	keep_window_open();
	return 0;
}
