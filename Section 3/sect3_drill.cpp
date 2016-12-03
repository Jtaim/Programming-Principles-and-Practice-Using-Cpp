//written by Jtaim
//date 19 Sept 2015
//updated 1 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3 Drill. This drill is to write a program that produces a 
simple form letter based on user input.
*/

#include <iostream>
#include <string>
#include "section3.h" //custom header

//C++ programs start by executing the function main
int main()
{
	using namespace std;
	cout << "Enter the name of the person you want to write to:" << endl;
    string first_name = "???";     // first_name is a variable of type string
    cin >> first_name;             // read characters into first_name
    cout << "Dear " << first_name << ',' << endl;
    cout << "\tHow are you? I am fine. I'm writing a simple program in C++\n";
    cout << "Enter a friends name:\n";
    cin >> first_name;
    cout << "Have you seen " << first_name << " lately?\n";
    cout << "What is your friends gender?" << "(Enter m for male and f for female)\n";
    char gender = 'o';
    cin >> gender;
    if(gender == 'm')
        cout << "If you see " << first_name << " ask him to call me.\n";
    if(gender == 'f')
        cout << "If you see " << first_name << " ask her to call me.\n";
    cout << "How old are you?\n";
    int age = -1;
    cin >> age;
    if(age <=0 || age >= 110)
        simple_error("you're kidding! ");
    cout << "I hear you just had a birthday and you are " << age << " years old.\n";
    if(age < 12)
        cout << "Next year you will be " << age+1 << ".\n";
    if(age == 17)
        cout << "Next year you will be able to vote.\n";
    if(age > 70)
        cout << "I hope you are enjoying retirement.\n";
	cout << "Yours sincerely,\n\n\nJtaim\n";     //add 2 blank lines for a signature
	keep_window_open();
    return 0;
}