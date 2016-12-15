//written by Jtaim
//date 29 Sept 2015
//updated 13 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 4 exercise 2. 
If we define the median of a sequence as “a number so that exactly as many elements come before 
it in the sequence as come after it,” fix the program in §4.6.3 so that it always prints out a median. 
Hint: A median need not be an element of the sequence.
*/

#include "section4.h" //custom header
#include <vector>
#include <algorithm>

// read some temperatures into a vector
int main()
{
	using std::cin;
	using std::cout;
	using std::endl;

	constexpr char TERMINATION = '|';

	std::vector<double> temps;	// temperatures
	cout << "Enter some temperature values and find the medium. " << TERMINATION << " to exit\n";
	double sum = 0;
	double temperature;
	bool exit_temperature_collect = false;
	while (!exit_temperature_collect)
	{
		if (cin >> temperature)
		{
			sum += temperature;
			temps.push_back(temperature);
		}
		else
		{
			// EOF is captured when using txt file
			if (cin.eof() || cin.bad())
			{
				cin.clear();
				exit_temperature_collect = true;
			}
			else
			{
				cin.clear();
				std::string s;
				getline(cin, s);
				if (find(s.begin(), s.end(), TERMINATION) != s.end())
				{
					exit_temperature_collect = true;
				}
				else
				{
					cout << "Entered incorrect value.\n";
				}
			}
		}
	}
	// compute mean temperature:
	if (temps.size() != 0)
	{
		cout << "Average number: " << sum / temps.size() << endl;
		// compute median temperature:
		// If n is odd then Median (M) = value of ((n + 1)/2)th item term.
		// If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
		std::sort(temps.begin(), temps.end());	// sort numbers
		if (temps.size() % 2)
		{
			cout << "Median number: " << temps[temps.size() / 2] << endl;
		}
		else
		{
			// if have even amount, remember vector index starts at zero
			cout << "Median number: " << (temps[temps.size() / 2 - 1] + temps[temps.size() / 2]) / 2 << endl;
		}
	}
	else
	{
		simple_error("No data was found\n");
	}
	keep_window_open();
	return 0;
}
