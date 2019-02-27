#include "Money.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Money::Money(std::string m)
    : m_cents{}, m_currency{}
{
    std::stringstream ss{m};
    if(!m.empty()){
        char c{};
        ss.get(c);
        if(c != '$') throw std::invalid_argument("expected $");
        m_currency = c;
        double amount{};
        if(!(ss >> amount)) throw std::invalid_argument("expected monitory amount");
        if(amount >= 0.005){
            m_cents = static_cast<long>(amount * 100);
            double round = (amount * 100 - m_cents);
            if(round >= 0.5){
                round < 0.5 ? m_cents : ++m_cents;
            }
            return;
        }
    }
    m_cents = 0;
}

std::string Money::get_cents()
{
    std::stringstream ss;
    ss << '$' << std::fixed << std::setprecision(2) << static_cast<double>(m_cents / 100.0);
    return ss.str();
}
