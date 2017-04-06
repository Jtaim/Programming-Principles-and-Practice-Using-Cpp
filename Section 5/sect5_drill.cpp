//written by Jtaim
//date 3 April 2017
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
	//Cout<<"Success!\n";
	//fixed miss spelling of cout
	cout << "Drill 1 Success!\n";

	//DRILL 2
	//cout<<"Success!\n;
	//fixed missing " 
	cout << "Drill 2 Success!\n";

	//DRILL 3
	//cout<<"Success"<<!\n";
	//fixed by removing a " and second <<
	cout << "Drill 3 Success!\n";

	//DRILL 4
	//cout<<success<<'\n';
	//fixed by placing " success "
	cout << "Drill 4 Success!" << "\n";

	//DRILL 5
	//string res=7;vector<int>v(10);v[5]=res;cout<<"Success!\n";
	//fixed by changing string type to int added range checking instead of raw []
	int res = 7;
	vector<int>v5(10);
	v5.at(5) = res;
	cout << "Drill 5 Success!\n";

	//DRILL 6
	//vector<int>v2(10);v2(5) = 7;if(v2(5) != 7)cout<<"Success!\n";
	//fixed by using [] not () for indexing elements of vector
	vector<int>v6(10);
	v6.at(5) = 7;		//.at() adds range checking
	if (v6.at(5) != 7) {
		cout << "Drill 6 Success!\n";
	}

	//DRILL 7
	//if (cond)cout << "Success!\n";else cout << "Fail!\n";
	//incomplete code condition logic
	bool d7 = true;
	if (d7 == true) {
		cout << "Drill 7 Success!\n";
	}

	//Drill 8
	//bool c = false; if (c)cout << "Success!\n";else cout << "Fail!\n";
	//legal but what changes bool c?
	//hard to read and "c" not very descriptive of what is being checked.
	bool d8 = false;
	if (d8 == false) {
		cout << "Drill 8 Success!\n";
	}
	else {
		cout << "Drill 8 Fail!\n";
	}

	//Drill 9
	//string s = "ape";boo c = "fool" < s;if (c)cout << "Success!\n";
	//is c a bool = false or c a string = "fool"
	//assuming c is bool?
	//hard to read and variables not very descriptive.
	string s9 = "ape";
	bool c9 = "fool" < s9;
	if (c9 == false) {
		cout << "Drill 9 Success!\n";
	}

	//Drill 10
	//string s = "ape";if (s == "fool") cout << "Success!\n";
	//legal but does not make sense
	//hard to read and variables not very descriptive.
	string s10 = "ape";
	if (s10 != "fool") {
		cout << "Drill 10 Success!\n";
	}

	//Drill 11
	//string s = "ape"; if (s == "fool")cout < "Success!\n";
	//missing second < after cout
	//does not make sense
	//question if condition and code hard to read
	string s11 = "ape";
	if (s11 != "fool") {
		cout << "Drill 11 Success!\n";
	}

	//Drill 12
	//string s = "ape"; if (s+"fool")cout < "Success!\n";
	//bad comparison expression and missing second < after cout
	//have no idea what is wanted here for a result
	string s12 = "Drill 12 Success!\n";
	cout << s12;

	//Drill 13
	//vector<char>v(5);for(int i = 0;0 < v.size();++i);cout << "Success!\n";
	//compiled but condition in for loop cause loop forever 0 aways less than size()
	vector<char>v13(5, '?');
	for (auto c : v13) {
		cout << c;
	}
	cout << " Drill 13 Success!\n";

	//Drill 14
	//vector<char>v(5);for(int i = 0;i<=v.size();++i);cout << "Success!\n";
	//compiled but condition for loop will cause range error
	//v.size() = 5 but iterations are 0 - 4
	vector<char>v14(5);
	for (auto c : v14) {
		cout << int(c);
	}
	cout << " Drill 14 Success!\n";

	//Drill 15
	//string s = "Success!\n";for (int i = 0;i < 6;++i)cout << s[i];
	//legal but no check for out of range, also string is larger do you want to truncate?
	string s15 = "Drill 15 Success!\n";
	const string::size_type maxPrint = 6;
	auto sStr = s15.substr(0, maxPrint);
	cout << sStr << '\n';
	
	//Drill 16
	//if(true)then cout << "Success!\n";else cout << "Fail!\n";
	//pysdo code can not be converted to C++ by the compiler
	if (true) {  //checking something
		cout << "Drill 16 Success!\n";
	}
	else {
		cout << "Drill 16 Fail!\n";
	}

	//Drill 17
	//int x = 2000;char c = x;if(c == 2000)cout << "Success!\n";
	//narrowing error going from int to a char
	int d17 = 100;
	char c17 = narrow_cast<char>(d17);
	cout << "Drill 17 Success! " << d17 << " " << c17 << '\n';
	
	//Drill 18
	//string s = "Success!\n";for (int i = 0;i < 10;++i)cout << s[i];
	//legal but no out of range checks
	//string s = "Success!\n";for (int i = 0;i < 10;++i)cout << s.at(i);
	//s.at() provides bound checking and will throw an exception
	//string s = "Success!\n";for (int i = 0;i < s.size();++i)cout << s.at(i);
	//compare against vector size is safer.
	string s18 = "Drill 18 Success!\n";
	for (auto i : s18) {
		cout << i;
	}
	
	//Drill 19
	//vector v(5);for (int i = 0;i <= v.size();++i);cout << "Success!\n";
	//compile error: argument list for class template "std::vector" is missing
	//vector<int> v(5);for (int i = 0;i <= v.size();++i);cout << "Success!\n";
	//no compile errors now but have an out of range issue with <=
	//vector<int> v(5);for (int i = 0;i < v.size();++i);cout << "Success!\n";
	vector<int> v19(5);
	for (int i = 0; i < v19.size(); ++i)
	{
		cout << v19[i];
	}
	cout << " Drill 19 Success!\n";

	//Drill 20
	//int i = 0;int j = 9;while (i < 10)++j;if (j < i)cout << "Success!\n";
	//will compile but in a while endless loop nothing increments i
	//if statement will never be true also with j incrementing
	int d20a = 0;
	int d20b = 9;
	while (d20a < 10) {
		++d20a;
	}
	if (d20b < d20a) {  // dDrill20a should now be 10
		cout << d20a << " Drill 20 Success!\n";
	}

	//Drill 21
	//int x = 2;double d = 5 / (x - 2);if (d == 2 * x + 0.5)cout << "Success!\n";
	//will compile but have divide by zero issue
	//plus comparing double to an int could have issues with int truncating decimal value
	int n21 = 3; //changed to 3
	double d21 = 5;
	d21 = 5.0 / (n21 - 2);
	if (d21 == (2 * n21 + 0.5)) {
		cout << "Drill 21 Success!\n";
	}
	else {
		cout << "can use quadratic equation to find Drill 21 success\n";
	}

	//Drill 22
	//string<char>s = "Success!\n";for (int i = 0;i <= 10;++i)cout << s[i];
	//compile error: type "std::string" may not have a template argument list
	string s22 = "Drill 22 Success!\n";
	//for (int i = 0;i <= 10;++i)cout << s22[i];
	//no there is no range checking
	for (auto i : s22)
	{
		cout << i;
	}

	//Drill 23
	//int i = 0;while (i < 10)++j;if(j < i)cout << "Success!\n";
	//Holy cow someone was up late drinking
	//magic numbers :(
	int n23a = 0;
	int n23b = 8; //mark last iteration
	while (n23a < 10)
	{
		if (n23b < n23a)
		{
			cout << "Drill 23 Success!\n";
		}
		++n23a;
	}

	//Drill 24
	//int x = 4;double d = 5 / (x - 2);if (d = 2 * x + 0.5)cout << "Success!\n";
	//will compile
	//narrowing error with d
	//divide check not made
	//if will always be true.  d == not d =
	int n24 = 4;	//why 4 and 2
	if (n24 == 2) { //check for divide by zero error
		error(string("divide by zero error"));
	}
	double d24 = 0;
	d24 = 5.0 / (n24 - 2);
	if (d24 == (2 * n24 + 0.5) / 3.4) { //adjusted and solved quadratic to get a pass
		cout << "Drill 24 Success!\n";
	}

	//Drill 25
	//cin << "Success!\n";
	//Compile error: no operator "<<" matches these operands
	//use cout
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
