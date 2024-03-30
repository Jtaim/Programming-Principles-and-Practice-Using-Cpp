#include "Money.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Money::Money( std::string m )
{
    auto valid{ validate_currency( m ) };
    if( !valid.empty() )
    {
        throw std::invalid_argument( valid );
    }
}

std::string Money::get_cents()
{
    std::stringstream ss;
    ss << m_currencySign << std::fixed << std::setprecision( 2 ) << ( static_cast<double>( m_cents / 100.0 ) * m_conversion );
    return ss.str();
}

Money Money::operator+( const Money& m ) const
{
    return Money{ std::string( this->m_currencyCode )
        + std::to_string( ( ( this->m_cents + m.m_cents ) / 100.0 ) * this->m_conversion ) };
}

std::string Money::validate_currency( const std::string& m )
{
    if( m.empty() )
    {
        m_cents = 0;
    }
    else
    {
        std::stringstream ss{ m };
        char c{};
        std::string temp_str;
        for( ; ss.get( c ) && ( !std::isdigit( c ) && c != '.' ); )
        {
            temp_str += c;
        }
        if( !ss.good() )
        {
            return "ERROR: unexpected stream error";
        }
        ss.putback( c );

        auto itr = std::find_if( currencyInfo.begin(), currencyInfo.end(),
                                 [temp_str]( currencyInfoTuple cit ) { return std::get<1>( cit ) == temp_str; } );
        if( itr == currencyInfo.cend() )
        {
            itr = std::find_if( currencyInfo.begin(), currencyInfo.end(),
                                [temp_str]( currencyInfoTuple cit ) { return std::get<0>( cit ) == temp_str; } );
            if( itr == currencyInfo.cend() )
            {
                return "ERROR: expected currency symbol";
            }
        }
        m_currencyCode = std::get<0>( *itr );
        m_currencySign = std::get<1>( *itr );
        m_conversion = std::get<2>( *itr );  // to USD for common standard

        double amount{};
        if( !( ss >> amount ) )
        {
            return "ERROR: invalid monitory amount";
        }
        else if( !ss.eof() )
        {
            return "ERROR: Data left in the stream";
        }
        else
        {
            amount /= m_conversion;
            if( amount > 0.004 )
            {
                m_cents = static_cast<long>( amount * 100 );
                if( ( amount * 100 - m_cents ) > 0.4 )
                {
                    ++m_cents;
                }
            }
            else
            {
                m_cents = 0;
            }
        }
    }
    return "";
}


std::ostream& operator<<( std::ostream& os, const Money& m )
{
    os << m.m_currencySign << std::fixed << std::setprecision( 2 ) << static_cast<double>( m.m_cents / 100.0 * m.m_conversion );
    return os;
}

std::istream& operator>>( std::istream& is, Money& m )
{
    std::string unvalidated_currency;
    is.exceptions( is.exceptions() | std::ios::badbit );
    is >> unvalidated_currency;
    if( is.fail() )
    {
        return is;
    }
    auto valid{ m.validate_currency( unvalidated_currency ) };
    if( !valid.empty() )
    {
        is.setstate( std::ios::failbit );
    }
    return is;
}
