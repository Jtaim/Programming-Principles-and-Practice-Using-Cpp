//written by Jtaim
//date 29 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 4 exercise 2. 
If we define the median of a sequence as “a number so that exactly as many elements come before 
it in the sequence as come after it,” fix the program in §4.6.3 so that it always prints out a median. 
Hint: A median need not be an element of the sequence.
*/

#include "section4.h" //custom header

// read some temperatures into a vector
int main()
{
    vector<double> temps;          // temperatures
    for (double temp; cin>>temp; ) // read into temp
        temps.push_back(temp);     // put temp into vector
	if (cin.eof())    // EOF is captured
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
    // compute mean temperature:
    double sum = 0;
    for (int x : temps) sum += x;
        cout << "Average number: " << sum/temps.size() << endl;

    // compute median temperature:
	// If n is odd then Median (M) = value of ((n + 1)/2)th item term.
	// If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
    sort(temps.begin(), temps.end()); // sort numbers
	if(temps.size()%2)
		cout << "Median number: " << temps[temps.size()/2] << endl;
	else
		cout << "Median number: " << (temps[temps.size()/2-1]+temps[temps.size()/2])/2 << endl; // if have even amount, remember vector index starts at zero
	keep_window_open();
	return 0;
}