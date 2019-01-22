#include "Patron.h"

namespace library
{

    Patron::Patron()
        : m_name(""), m_card_number(0), m_fees(0.0)
    {}

    Patron::Patron(const std::string name, const int card_number)
        : m_name(name), m_card_number(card_number), m_fees(0.0)
    {}

    double Patron::get_fees() const
    {
        if(m_fees < 0.01){
            return 0.0;
        }
        return m_fees;
    }

    double Patron::set_fees(const double f)
    {
        m_fees += f;
        return get_fees();
    }

    bool Patron::is_outstanding_fee() const
    {
        return m_fees >= 0.01;
    }

    std::ostream & operator<<(std::ostream & os, const Patron & p)
    {
        os << p.m_name << '\n' << p.m_card_number;
        return os;
    }

    bool operator==(const Patron & p1, const Patron & p2)
    {
        return (p1.m_name == p2.m_name && p1.m_card_number == p2.m_card_number);
    }

    bool operator!=(const Patron & p1, const Patron & p2)
    {
        return !(p1 == p2);
    }

}
