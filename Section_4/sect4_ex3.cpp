//written by Jtaim
//date 31 Mar 2017
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
    using namespace std;

    constexpr auto termination{ '|' };

    std::vector<double> dist;
    auto sum{ 0.0 };
    auto min{ 0.0 };
    auto max{ 0.0 };

    cout << "Please enter sequence of doubles (representing distances). '" << termination << "' to exit:\n";
    auto distance{ 0.0 };
    auto exit{ false };
    while (!exit) {
        if (cin >> distance) {
            if (distance <= 0) {
                cout << "a distance of zero or less is not allowed.\n";
            }
            else {
                if (sum == 0) {
                    min = max = distance;
                }
                else if (distance < min) {
                    min = distance;
                }
                else if (distance > max) {
                    max = distance;
                }
                else {
                    simple_error("should not be here.\n");
                }
                sum += distance;
                dist.push_back(distance);
            }
        }
        else {
            if (cin.eof()) {
                cin.clear();
                exit = true;
            }
            else {
                cin.clear();
                char temp;
                cin >> temp;
                if (temp == termination) {
                    exit = true;
                }
                else {
                    cout << "Entered incorrect value.\n";
                }
            }
        }
    }
    if (dist.size() == 0) {
        cout << "no distances entered\n";
    }
    else {
        cout << "total distance " << sum << endl;
        cout << "smallest distance " << min << endl;
        cout << "greatest distance " << max << endl;
        cout << "mean distance " << sum / dist.size() << endl;
    }
    keep_window_open();
    return 0;
}
