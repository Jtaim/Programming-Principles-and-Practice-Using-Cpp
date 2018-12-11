#include "symbol_table.h"

#include <algorithm>

calculator::Symbol_Table::Symbol_Table()
{
}

calculator::Symbol_Table::~Symbol_Table()
{
}

/// return the value of the Variable with the input name.
double calculator::Symbol_Table::get_value(const std::string &s)
{
    auto vt = find_value(var_table.cbegin(), var_table.cend(), s);
    if (vt == var_table.cend()) throw std::runtime_error("get: undefined name " + s);
    return vt->value;
}

/// set the Variable of the named to a double value.
void calculator::Symbol_Table::set_value(const std::string &s, const double d)
{
    auto vt = find_value(var_table.begin(), var_table.end(), s);
    if (vt == var_table.cend()) throw std::runtime_error("get: undefined name " + s);
    vt->value = d;
}

/// is a name already declared
bool calculator::Symbol_Table::is_declared(const std::string &s)
{
    auto vt = find_value(var_table.cbegin(), var_table.cend(), s);
    return vt != var_table.cend();
}

/// add name value to a vector of Variables
double calculator::Symbol_Table::declare(const std::string &s, const double d)
{
    if (is_declared(s)) throw std::runtime_error(s + " declared twice");
    var_table.push_back(Variable{ s, d });
    return d;
}
