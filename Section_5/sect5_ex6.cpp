//written by Jtaim
//date 6 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 6
Celsius to Fahrenheit converter
Fahrenheit to Celsius converter
*/
#include "section5.h"

// converts Celsius to Fahrenheit f=9/5*c+32
double ctof(double cToF)
{
    //throw error if value given in Celsius is below -273.15
    if (cToF < -273.15) {
        error("ctof can not convert below absolute zero!\n");
    }
    cToF = (9.0 / 5 * cToF + 32);
    return cToF;
}
// converts Kelvin to Celsius
double ftoc(double fToC)
{
    fToC = (5.0 / 9 * (fToC - 32));
    //throw error if value given in Celsius is below -273.15
    if (fToC < -273.15) {
        error("ftoc can not convert below absolute zero!\n");
    }
    return fToC;
}

int main()
try
{
    using std::cout;
    using std::cin;
    bool badConverion = false;
    do {
        badConverion = false;
        cout << "Enter a temperature and unit of temperature (c = Celsius, f = Fahrenheit)\n";
        double temp_to_convert{ 0.0 }; //input temperature variable
        while (!(cin >> temp_to_convert)) {
            cin.clear();  //clear cin error flags
            cin.ignore(UINT8_MAX, '\n'); //clear cin buffer
            cout << "entered non-numeric temperature.  Re-enter\n";
        }
        char entered_temp_unit{ '?' };
        cin >> entered_temp_unit;
        entered_temp_unit = tolower(entered_temp_unit);

        double converted_temp{ 0.0 };
        char converted_temp_unit{ '?' };
        switch (entered_temp_unit) {
        case 'f':
            converted_temp = ftoc(temp_to_convert);
            converted_temp_unit = 'c';
            break;
        case 'c':
            converted_temp = ctof(temp_to_convert);
            converted_temp_unit = 'f';
            break;
        default:
            badConverion = true;
            cout << "entered wrong temperature unit of measure. re-enter conversions\n";
        }
        if (badConverion == false) {
            cout << "Converted temperature is " << converted_temp << converted_temp_unit << '\n';
        }
    } while (badConverion);
    keep_window_open();
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}
