//written by Jtaim
//date 27 Oct 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 drills
*/
#include "section5.h"

int main()
try
{
	using namespace std;

	//DRILL 1
	//Cout<<"Success!\n"; //compile error: identifier "Cout" is undefined
	cout << "Drill 1 Success!\n";

	//DRILL 2
	//cout<<"Success!\n;  //compile error: missing closing quote
						  //compile error: expected a ';'
	cout << "Drill 2 Success!\n";

	//DRILL 3
	//cout<<"Success"<<!\n";  //compile error: unrecognized token
							  //compile error: missing closing quote
	//cout<<"Success"<<"!\n"; //legal but hard to read
	cout << "Drill 3 Success!\n";

	//DRILL 4
	//cout<<success<<'\n';  //compile error: identifier "success" is undefined
	//cout<<"success"<<'\n';//legal but hard to read
	cout << "Drill 4 Success!\n";

	//DRILL 5
	//string res=7;vector<int>v(10);v[5]=res;cout<<"Success!\n";
	//compile error: no suitable constructor exists to convert from "int" to "std::basic_string<char, std::char_traits<char>, std::allocator<char>>"
	//compile error: no suitable conversion function from "std::string" to "int" exists
	//so assuming wanted int type not string type
	//int res = 7;vector<int>v(10);v[5] = res;cout << "Success!\n";
	//legal but hard to read
	int nRes = 7;
	vector<int>v5(10); //initialize vector with 10 elements
	v5[5] = nRes;       //be careful of a range error
	cout << "Drill 5 Success!\n";

	//DRILL 6
	//vector<int>v2(10);v2(5) = 7;if(v2(5) != 7)cout<<"Success!\n";
	//compile error: call of an object of a class type without appropriate operator() or conversion functions to pointer - to - function type
	//vector<int>v2(10);v2[5] = 7;if(v2[5] != 7)cout<<"Success!\n";
	//legal but hard to read plus if statement seems wrong
	vector<int>v6(10); //initialize vector with 10 elements
	v6[5] = 7;         //be careful of a range error
	if (v6[5] == 7)
	{  //seems to make more sense
		cout << "Drill 6 Success!\n";
	}

	//DRILL 7
	//if (cond)cout << "Success!\n";else cout << "Fail!\n";
	//compile error: identified "cond" is undefined
	//not sure what condition to check so and hard to read
	bool bDrill7 = true;
	cout << (bDrill7 ? "Drill 7 Success!\n" : "Drill 7 Fail!\n");

	//Drill 8
	//bool c = false; if (c)cout << "Success!\n";else cout << "Fail!\n";
	//legal but not what changes bool c?
	//hard to read and "c" not very descriptive of what is being checked.
	bool bDrill8 = false;
	cout << (bDrill8 ? "Drill 8 Fail!\n" : "Drill 8 Success!\n");

	//Drill 9
	//string s = "ape";boo c = "fool" < s;if (c)cout << "Success!\n";
	//compile error: identified "boo" is undefined
	//hard to read and variables not very descriptive.
	string strDrill9 = "ape";
	if (strDrill9 <= "fool")
	{ //magic comparison
		cout << "Drill 9 Success!\n";
	}

	//Drill 10
	//string s = "ape";if (s == "fool") cout << "Success!\n";
	//legal but does not make sense
	//hard to read and variables not very descriptive.
	string strDrill10 = "ape";
	if (strDrill10 != "fool")
	{
		cout << "Drill 10 Success!\n";
	}

	//Drill 11
	//string s = "ape"; if (s == "fool")cout < "Success!\n";
	//compile error: no operator "<" matches these operands
	//string s = "ape"; if (s == "fool")cout << "Success!\n";
	//legal but question if condition and code hard to read
	string strDrill11 = "ape";
	if (strDrill11 != "fool")
	{
		cout << "Drill 11 Success!\n";
	}

	//Drill 12
	//string s = "ape"; if (s+"fool")cout < "Success!\n";
	//compile error: expression must have bool type (or be convertible to bool)
	//compile error: no operator "<" matches these operands
	//not logic error in if statement condition
	string strDrill12 = "ape";
	if (strDrill12 != "fool")
	{
		cout << "Drill 12 Success!\n";
	}

	//Drill 13
	//vector<char>v(5);for(int i = 0;0 < v.size();++i);cout << "Success!\n";
	//compiled but condition in for loop cause loop forever 0 aways less than size()
	vector<char>v13(5);
	for (decltype(v13.size()) i = 0;i < v13.size();++i)
	{
		cout << i << " ";
	}
	cout << "Drill 13 Success!\n";

	//Drill 14
	//vector<char>v(5);for(int i = 0;i<=v.size();++i);cout << "Success!\n";
	//compiled but condition in for loop would cause range error if accessing something from the vector
	//v.size() = 5 but iterations are 0 - 4
	vector<char>v14(5);
	for (decltype(v14.size()) i = 0;i < v14.size();++i)
	{
		v14.at(i) = static_cast<char>(97 + i); // 97 = ASCII 'a'
	}
	for (auto i : v14)
	{
		cout << i << " ";
	}
	cout << "Drill 14 Success!\n";

	//Drill 15
	//string s = "Success!\n";for (int i = 0;i < 6;++i)cout << s[i];
	//legal but no check for out of range. do also && to i<s.size()
	//or use s.at(i) to throw exception if out of bounds
	string strDrill15 = "Drill 15 Success!\n";
	decltype(strDrill15.size()) dMax = 1024; //max characters I want
	for (decltype(strDrill15.size()) i = 0; i < dMax && i < strDrill15.size(); ++i)
	{
		cout << strDrill15.at(i);
	}

	//Drill 16
	//if(true)then cout << "Success!\n";else cout << "Fail!\n";
	//compile error: identifier "then" is undefined
	//compile error: expected a ';'
	if (true)
	{  //checking something
		cout << "Drill 16 Success!\n";
	}
	else
	{
		cout << "Drill 16 Fail!\n";
	}

	//Drill 17
	//int x = 2000;char c = x;if(c == 2000)cout << "Success!\n";
	//narrowing error going from int to a char
	int nDrill17 = 100;
	char cDrill17 = nDrill17;
	if (nDrill17 != cDrill17)
	{ //limit is -128 to 127
		error(string("info loss"));
	}
	else
	{
		cout << "Drill 17 Success!\n";
	}

	//Drill 18
	//string s = "Success!\n";for (int i = 0;i < 10;++i)cout << s[i];
	//legal but no out of range checks 10 over ran the range
	//string s = "Success!\n";for (int i = 0;i < 10;++i)cout << s.at(i);
	//s.at() provides bound checking and will throw an exception
	//string s = "Success!\n";for (int i = 0;i < s.size();++i)cout << s.at(i);
	//compare against vector size is safer.
	string strDrill18 = "Drill 18 Success!\n";
	for (auto i : strDrill18)
	{
		cout << i;
	}
	//range for is best way to iterate threw the string in this case

	//Drill 19
	//vector v(5);for (int i = 0;i <= v.size();++i);cout << "Success!\n";
	//compile error: argument list for class template "std::vector" is missing
	//vector<int> v(5);for (int i = 0;i <= v.size();++i);cout << "Success!\n";
	//no compile errors now but have a out of range issue
	//vector<int> v(5);for (int i = 0;i < v.size();++i);cout << "Success!\n";
	vector<int> v19(5);
	for (decltype(v19.size()) i = 0; i < v19.size();++i)
	{
		cout << i << " ";
	}
	cout << "Drill 19 Success!\n";

	//Drill 20
	//int i = 0;int j = 9;while (i < 10)++j;if (j < i)cout << "Success!\n";
	//will compile but in a while endless loop nothing increments i
	//if statement will never be true also with j incrementing
	int nDrill20a = 0;
	int nDrill20b = 9;
	while (nDrill20a < 10)
	{
		++nDrill20a;
	}
	if (nDrill20b < nDrill20a) {  // dDrill20a should now be 10
		cout << nDrill20a << " Drill 20 Success!\n";
	}

	//Drill 21
	//int x = 2;double d = 5 / (x - 2);if (d == 2 * x + 0.5)cout << "Success!\n";
	//will compile
	//narrowing error with d
	//divide check not made
	//not sure if good idea to use float for comparison
	//plus comparing double to an int could have issues with int truncating decimal value
	int nDrill21 = 6;  //why 6, cant do all for you
	if (nDrill21 == 2) { //check for divide by zero error
		error(string("divide by zero error"));
	}
	double dDrill21 = 0;
	dDrill21 = static_cast<double>(5) / (nDrill21 - 2);
	if (dDrill21 == static_cast<double>(2 * nDrill21 + 0.5) / 10) { //adjusted and solved quadratic to get a pass
		cout << "Drill 21 Success!\n";
	}

	//Drill 22
	//string<char>s = "Success!\n";for (int i = 0;i <= 10;++i)cout << s[i];
	//compile error: type "std::string" may not have a template argument list
	//vector<char>vDrill22 = { 'S','u','c','c','e','s','s','!','\n' };
	//for (int i = 0;i <= 10;++i)cout << vDrill22[i];
	//got a runtime error in VS2015 and odd extra character when using GNU GCC
	//vector<char>vDrill22 = { 'S','u','c','c','e','s','s','!','\n' };
	//for (int i = 0;i <= 10;++i)cout << vDrill22.at(i);
	//now got runtime error in both compilers
	vector<char>vDrill22 = { 'D','r','i','l','l',' ','2','2',' ','S','u','c','c','e','s','s','!','\n' };
	for (auto i : vDrill22)
	{
		cout << i;
	}

	//Drill 23
	//int i = 0;while (i < 10)++j;if(j < i)cout << "Success!\n";
	//Holy cow someone was up late drinking
	int nDrill23a = 0;
	int nDrill23b = 8; //mark last iteration
	while (nDrill23a < 10)
	{
		cout << nDrill23a << " ";
		if (nDrill23b < nDrill23a)
		{
			cout << "Drill 23 Success!\n";
		}
		++nDrill23a;
	}

	//Drill 24
	//int x = 4;double d = 5 / (x - 2);if (d = 2 * x + 0.5)cout << "Success!\n";
	//will compile
	//narrowing error with d
	//divide check not made
	//if will always be true.  d == not d =
	int nDrill24 = 4;	//why 6, cant do all for you
	if (nDrill24 == 2)
	{ //check for divide by zero error
		error(string("divide by zero error"));
	}
	double dDrill24 = 0;
	dDrill24 = static_cast<double>(5) / (nDrill24 - 2);
	if (dDrill24 == static_cast<double>(2 * nDrill24 + 0.5) / 3.4)
	{ //adjusted and solved quadratic to get a pass
		cout << "Drill 24 Success!\n";
	}

	//Drill 25
	//cin << "Success!\n";
	//Compile error: no operator "<<" matches these operands
	cout << "Drill 25 Success!\n";

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
