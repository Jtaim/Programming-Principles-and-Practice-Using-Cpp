//written by Jtaim
//date 30 Mar 2017
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
    using namespace std;

    constexpr char termination = '|';

    std::vector<double> temperatures;	// temperatures
    cout << "Enter some temperature values and find the medium. " << termination << " to exit\n";
    double sum{ 0.0 };
    double temperature{ 0.0 };
    bool exit_temperature_collect{ false };
    while (!exit_temperature_collect)
    {
        if (cin >> temperature)
        {
            sum += temperature;
            temperatures.push_back(temperature);
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
                char c;
                cin >> c;
                if (c == termination)
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
    if (temperatures.size() != 0)
    {
        cout << "Average number: " << sum / temperatures.size() << endl;
        // compute median temperature:
        // If n is odd then Median (M) = value of ((n + 1)/2)th item term.
        // If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
        sort(temperatures.begin(), temperatures.end());	// sort numbers
        if ((temperatures.size() % 2) > 0)
        {
            cout << "Median number: " << temperatures[temperatures.size() / 2] << endl;
        }
        else
        {
            // if have even amount, remember vector index starts at zero
            // get 2 middle indexes and divide by 2
            cout << "Median number: " << (temperatures[temperatures.size() / 2 - 1] + temperatures[temperatures.size() / 2]) / 2 << endl;
        }
    }
    else
    {
        cout << "No data was found\n";
    }
    keep_window_open();
    return 0;
}
