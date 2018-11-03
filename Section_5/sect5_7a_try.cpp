//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.7 first one
build and test the program from the section.
Does it provide the correct results?
What is the lease amount of input you can give it to get it to fail?
*/

#include "section5.h"

int main()
{
    using namespace std;

    cout << "Enters some temperatures in Fahrenheit.  EOF to exit\n";
    std::vector<double>temps;	// temperatures
    while (true)
    {
        auto temp{ 0.0 };
        if (cin >> temp) {
            temps.push_back(temp);
        }
        else if (cin.eof()) {
            break;
        }
        else {
            cout << "bad temperature entry\n";
            cin.clear();
            cin.get();
        }
    }
    // check for empty vector
    if (temps.size() != 0) {
        std::sort(temps.begin(), temps.end());
        auto sum = std::accumulate(temps.begin(), temps.end(), 0.0);
        cout << "High temperature: " << temps.back() << endl;
        cout << "Low temperature: " << temps.front() << endl;
        cout << "Average temperature: " << sum / temps.size() << endl;
    }
    else {
        cout << "No temperatures entered.\n";
    }
    keep_window_open();
    return 0;
}
