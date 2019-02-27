
#ifndef MONEY_CLASS_H	// begin header guard
#define MONEY_CLASS_H

#include <string>
#include <vector>

class Money{
public:
    Money(std::string m = "");

    std::string get_cents();

    static std::vector<std::pair<std::string, int>> conversion;

private:
    // amount in cents.  lowest denomination
    long m_cents;
    std::string m_currency;
};

#endif