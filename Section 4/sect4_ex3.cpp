//written by Jtaim
//date 29 Sept 2015
//updated 14 Dec 2016
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
#include <vector>

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	std::vector<double> dist;
	double sum = 0;
	double min = 0;
	double max = 0;

	cout << "please enter sequence of doubles (representing distances):\n";
	double distance = 0;
	while (cin >> distance)
	{
		if (distance <= 0)
			cout << "a distance of zero or less is not allowed.\n";
		else
		{
			if (sum == 0)
			{
				min = max = distance;
			}
			else if (distance < min)
				min = distance;
			if (distance > max)
				max = distance;
			sum += distance;
			dist.push_back(distance);
		}
	}
	cin.clear();
	cin.ignore(32768, '\n');
	if (dist.size() == 0)
		cout << "no distances entered\n";
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
