#include "../includes/ppp.h"

namespace X
{
	int var{};

	void print()
	{
		std::cout << "Printing from namespace X the value " << var << "\n";
	}
}

namespace Y
{
	int var{};

	void print()
	{
		std::cout << "Printing from namespace Y the value " << var << "\n";
	}
}

namespace Z
{
	int var{};

	void print()
	{
		std::cout << "Printing from namespace Z the value " << var << "\n";
	}
}

int main()
{
	X::var = 7;
	X::print();
	using namespace Y;
	var = 9;
	print();
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();
	}
	print();
	X::print();

	ppp::keep_window_open();
	return 0;
}