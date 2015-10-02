//written by Jtaim
//date 29 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 3. 
Read a sequence of double values into a vector. 
Think of each value as the distance between two cities along a given route. 
Compute and print the total distance (the sum of all distances). 
Find and print the smallest and greatest distance between two neighboring cities. 
Find and print the mean distance between two neighboring cities.
*/

#include "section4.h" //custom header

int main()
{
	vector<double> dist;
	double sum = 0;	
	double min = 0;
	double max = 0;
	
	cout << "please enter sequence of doubles (representing distances):\n";
	double val = 0;
    while(cin>>val)  // read into val
	{
        if(val<=0)
			cerr << "What really number 0 or less for distance.\n";
		else
		{
			dist.push_back(val);
			sum += val;
			if (val < min || min == 0) // includes how to deal with initial value zero
			    min = val;
			if (max < val)
			    max = val;
		}
	}
	if (cin.eof())    // EOF is captured
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
    if(dist.size() == 0)
		cerr << "no distances\n";
	else
	{
		cout << "total distance " << sum << endl;
		cout << "smallest distance " << min << endl;
		cout << "greatest distance " << max << endl;
		cout << "mean distance " << sum / dist.size() << endl;
	}
	keep_window_open();
	return 0;
}