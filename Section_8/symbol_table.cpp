#include "symbol_table.h"

#include <algorithm>

calculator::Symbol_Table::Symbol_Table()
{
}

calculator::Symbol_Table::~Symbol_Table()
{
}

/// return the value of the Variable with the input name.
double calculator::Symbol_Table::get_value(const std::string s)
{
    auto vt = std::find(var_table.begin(), var_table.end(), s);
    if (vt == var_table.end()) throw std::runtime_error("get: undefined name " + s);
    return vt->value;
}

/// set the Variable of the named to a double value.
void calculator::Symbol_Table::set_value(const std::string s, const double d)
{
    auto vt = std::find(var_table.begin(), var_table.end(), s);
    if (vt == var_table.end()) throw std::runtime_error("get: undefined name " + s);
    vt->value = d;
}

/// is a name already declared
bool calculator::Symbol_Table::is_declared(const std::string s)
{
    auto vt = std::find(var_table.begin(), var_table.end(), s);
    return vt != var_table.end();
}

/// add name value to a vector of Variables
double calculator::Symbol_Table::define_name(const std::string s, const double d)
{
    if (is_declared(s)) throw std::runtime_error(s + " declared twice");
    var_table.push_back(Variable{ s, d });
    return d;
}

bool calculator::operator==(const calculator::Variable &v, const std::string &s)
{
    return v.name == s;
}

bool calculator::operator==(const std::string &s, const calculator::Variable &v)
{
    return v.name == s;
}
