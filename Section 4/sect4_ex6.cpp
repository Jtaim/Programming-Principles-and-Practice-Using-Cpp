//written by James Weiland
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 6. 
Make a vector holding the ten string values "zero", "one", . . . "nine". 
Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output seven. 
Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input seven gives the output 7.
*/

#include "std_lib_facilities.h" 							// custom header

vector<string> numbers;

void init_nums()
{
	numbers.push_back("zero");
	numbers.push_back("one");
	numbers.push_back("two");
	numbers.push_back("three");
	numbers.push_back("four");
	numbers.push_back("five");
	numbers.push_back("six");
	numbers.push_back("seven");
	numbers.push_back("eight");
	numbers.push_back("nine");
}

int main()
try
{
	init_nums();
	while(true)
	{
		const int not_a_symbol = numbers.size();	// not_a_symbol is a value that does not correspond
												    // to a string in the numbers vector
		int val = not_a_symbol;
		cout << "enter a number between 0 and 9: ";
		if(cin >> val)
		{
			cout << val << " is " << numbers[val] << endl;
			//break;
		}
		cin.clear();	// clear string after failed attempt to read an integer
		string s;
		cin>>s;
		//{
			for(unsigned i=0; i<numbers.size(); i++)	// see if the string is in numbers
			{
				if (numbers[i]==s)
					{
						val = i;
						break;
					}
				else 
					val = not_a_symbol;
			}
			if (val>=not_a_symbol) error("unexpected number string: ",s);
			cout << s <<  " is " << val << endl;
		//}
	}
	return 0;
}
catch (runtime_error e) {
	// this code is to produce error messages; it will be described in Chapter 5
	cout << e.what() << endl;
}
catch (...) {
	// this code is to produce error messages; it will be described in Chapter 5
	cout << "exiting\n";
}
	
	