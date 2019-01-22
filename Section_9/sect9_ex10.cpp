/*
    Written by Jtaim
    Date 20 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 10
    A snippet of a leap year implementation for this chapters Date class
*/

/*
    formula for calculating leap years for the Gregorian calender:
    - The year is evenly divisible by 4;
    - If the year can be evenly divided by 100, it is NOT a leap year, unless;
    - The year is also evenly divisible by 400: Then it is a leap year.
*/
bool leap_year(int y)
{
    if(!(y % 400)){
        return true;
    }
    if(y % 100 && !(y % 4)){
        return true;
    }
    return false;
}