//Written by Jtaim
//Date 2 Dec 2015
//updated 28 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 9
read digits and compose them into integers. For example, 123 is read as the characters 1, 2, and 3.
Output of 123 is 1 hundred and 2 tens and 3 ones.
The numbers is output as int value.
Handle up to 4 digits.
terminate program with '|'.
*/

#include "section6.h"

bool input_check(std::vector<int>& dig, const char term);
void print_number(const std::vector<int>& dig, const std::vector<std::string> &denom);

int main()
{
	using std::cout;
	using std::cin;

	const char TERM = '|';
	// only have to add or subtract denominations and program will adjust
	const std::vector<std::string> DENOMINATION{ "thousands", "hundreds", "tens", "ones" };
	const size_t MAX_DIGITS = DENOMINATION.size();

	try
	{
		cout << "Enter a number up to " << MAX_DIGITS << " digits long. Enter " << TERM << " to exit\n";
		std::vector<int> numbers{};
		numbers.reserve(MAX_DIGITS);	// to reserve max capacity of the vector for error checking
		while (true)
		{
			if (input_check(numbers, TERM))
			{
				print_number(numbers, DENOMINATION);
			}
			else
			{
				break;
			}
		}
		cout << "Bye";
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
}

/* function to for valid entry (is a digit).
INPUT:	reference int vector to store valid numbers and const char for termination 
OUPUT:	bool: true = valid number sequence, false = termination found
ERROR:	if cin.fail() is set
loops until finds valid entry or finds termination character
*/
bool input_check(std::vector<int>& dig, const char term)
{
	dig.clear();
	bool good_bad = false;
	std::string str{ '?' };
	while (!good_bad)
	{
		std::cin >> str;
		if (!std::cin.good())
		{
			error("cin.fail() set to 1 when getting data.\n");
		}
		// if termination found set bool and break from loop 
		else if (find(str.begin(), str.end(), term) != str.end())
		{
			good_bad = false;
			break;
		}
		// check if entry is an integer
		else if (std::all_of(str.begin(), str.end(), std::isdigit))
		{
			// check that string is <= integer vector capacity
			if (str.size() > dig.capacity())
			{
				std::cout << "Digit entry is larger than know denomination.\n";
				good_bad = false;
			}
			else
			{
				// convert to integer
				for (auto i : str)
				{
					dig.push_back(i - '0');
				}
				good_bad = true;
			}
		}
		else
		{
			std::cout << "Digit entered is not an integer.\n";
			std::cin.ignore(INT16_MAX, '\n');
			good_bad = false;
		}
	}
	return good_bad;
}

/* function to for valid entry (is a digit).
INPUT:	reference const vector of int numbers and reference const vector of denominations
OUPUT:	none
ERROR:	if denomination vector size is < input integer vector size
will output number and denomination
*/
void print_number(const std::vector<int>& dig, const std::vector<std::string> &denom)
{
	if (dig.size() <= denom.size())
	{
		size_t index_offset = denom.size() - dig.size();	// align denom to number size 
		for (size_t i = 0; i < dig.size(); ++i)
		{
			if ((dig.size() - 1) == i)	// determine if last element
			{
				std::cout << dig[i] << " " << denom[i + index_offset] << ".\n";
			}
			else
			{
				std::cout << dig[i] << " " << denom[i + index_offset] << " and ";
			}
		}
	}
	else
	{
		error("denomination vector must be >= input vector.\n");
	}
}
