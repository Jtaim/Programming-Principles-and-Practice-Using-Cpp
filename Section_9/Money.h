
#ifndef MONEY_CLASS_H	// begin header guard
#define MONEY_CLASS_H

#include <string>
#include <vector>

using currencyInfoTuple = std::tuple<std::string, std::string, double>;
static const std::vector<currencyInfoTuple> currencyInfo
{
	{"USD", "$", 1},
	{"DKK", "Kr", 6.8}
};

class Money
{
public:
	Money(std::string m = "");

	std::string get_cents();

	static std::vector<std::pair<std::string, int>> conversion;

private:
	std::string m_currencyCode;
	std::string m_currencySign;
	long m_cents{};	// amount in cents.  lowest denomination
};

#endif