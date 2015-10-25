//written by Jtaim
//date 20 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.5
compile and test the program from this section.
*/

#include "section5.h" //custom header

//****************************************************************************
int area(int length, int width)         // calculate area of a rectangle
										// error-condition: length or width are negative
										// error-condition: result overflowed
{
	if (length <= 0 || width <= 0) {
		cout << "area() condition <= 0 error\n";
		return 0;
	}
	int a = length*width;
	if (a <= 0) {
		cout << "area() exceeded positive integer overflow error\n";
		return 0;
	}
	return a;
}
//****************************************************************************
int framed_area(int x, int y)             // calculate area within frame
										  // calculate frame width;
										  // error-conditions: length or width are negative
{
	constexpr int frame_width = 2;
	x -= frame_width;
	y -= frame_width;
	if (x <= 0 || y <= 0) {
		cout << "frame_width() condition <= 0 error\n";
		return 0;
	}
	return area(x,y);
}
//*****************************************************************************
int main()
{
	int x = 200000;
	int y = 300000;
	int z = 500000;
	int area1 = area(x, y);
	cout << "area1 = " << area1 << endl;
	int area2 = framed_area(3, z);
	cout << "area2 = " << area2 << endl;
	int area3 = framed_area(y, z);
	cout << "area3 = " << area3 << endl;
	if (area3 == 0) {
		cout << "div by 0 error\n";
	}
	else {
		double ratio = double(area1) / area3;        // convert to double to get
													 // floating-point division
		cout << "ratio = " << ratio << endl;
	}
	keep_window_open();
	return 0;
}