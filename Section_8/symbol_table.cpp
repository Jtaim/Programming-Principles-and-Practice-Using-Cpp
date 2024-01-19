#include "symbol_table.hpp"
#include "../includes/ppp.hpp"

#include <algorithm>

namespace calculator
{
    // return the value of the Variable with the input name.
    double Symbol_Table::get_value( const std::string_view s )
    {
        auto vt = find_name( var_table.begin(), var_table.end(), s );
        if( vt == var_table.end() )
        {
            ppp::error( "get: undefined name ", s.data() );
        }
        return vt->value;
    }

    // set the Variable of the named to a double value.
    void Symbol_Table::set_value( const std::string_view s, const double d )
    {
        auto vt = find_name( var_table.begin(), var_table.end(), s );
        if( vt == var_table.end() )
        {
            ppp::error( "set: undefined name ", s.data() );
        }
        if( vt->is_const )
        {
            ppp::error( "set: is a constant" );
        }
        vt->value = d;
    }

    // is a name already declared
    bool Symbol_Table::is_declared( const std::string_view s )
    {
        auto vt = find_name( var_table.begin(), var_table.end(), s );
        return vt != var_table.end();
    }

    // add name value to a vector of Variables
    double Symbol_Table::declare( const std::string_view s, const double d, const bool set_const )
    {
        if( is_declared( s ) )
        {
            ppp::error( s.data(), " declared twice" );
        }
        var_table.push_back( Variable{ s.data(), d, set_const } );
        return d;
    }
}  // calculator
