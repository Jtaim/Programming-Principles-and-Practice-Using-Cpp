
#ifndef MONEY_CLASS_H	// begin header guard
#define MONEY_CLASS_H

#include <string>
#include <vector>

class Money
{
public:
    Money( std::string m = "" );

    std::string get_cents();

    Money operator+( const Money& m ) const;
    friend std::ostream& operator<<( std::ostream& os, const Money& m );
    friend std::istream& operator>>( std::istream& is, Money& m );

private:
    std::string m_currencyCode{ "USD" };
    std::string m_currencySign{ "$" };
    long m_cents{};	// amount in cents.  lowest denomination stored in USD
    double m_conversion{};

    std::string validate_currency( const std::string& m );

    using currencyInfoTuple = std::tuple<std::string, std::string, double>;
    const std::vector<currencyInfoTuple> currencyInfo
    {
        {"USD", "$", 1}, // keep USD first because used as the standard stored currency
        {"DKK", "Kr", 6.8}
    };
};

#endif