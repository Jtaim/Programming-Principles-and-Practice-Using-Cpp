//written by Jtaim
//date 22 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.5.1
Implement square() without using the multiplication operator; 
that is, do the x*x by repeated addition (start a variable result at 0 and add x to it x times). 
Then run some version of “the first program” using that square().
*/

#include "section4.h" //custom header
int square(int);

int main()
{
    for(int num=1;num<=100;num++)
    {
        cout << square(num) << endl;
    }
	keep_window_open();
    return 0;
}

int square(int i)
{
	int result = 0;
		for(int j=0;j<i;j++) // do repeat addition not multiplication
		{
			result += i;
		}
	return result;
}