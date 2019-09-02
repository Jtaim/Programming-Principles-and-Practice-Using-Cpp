#include "symbol_table.h"
#include "../includes/ppp.h"

#include <algorithm>

namespace ppp_calc
{

	Symbol_Table::Symbol_Table()
	{}

	Symbol_Table::~Symbol_Table()
	{}

	/// return the value of the Variable with the input name.
	double Symbol_Table::get_value(const std::string& s)
	{
		auto vt = find_name(var_table.cbegin(), var_table.cend(), s);
		if(vt == var_table.cend()) ppp::error("get: undefined name ", s);
		return vt->value;
	}

	/// set the Variable of the named to a double value.
	void Symbol_Table::set_value(const std::string& s, const double d)
	{
		auto vt = find_name(var_table.begin(), var_table.end(), s);
		if(vt == var_table.cend()) ppp::error("set: undefined name ", s);
		if(vt->is_const) ppp::error(s, ": is a constant");
		vt->value = d;
	}

	/// is a name already declared
	bool Symbol_Table::is_declared(const std::string& s)
	{
		auto vt = find_name(var_table.cbegin(), var_table.cend(), s);
		return vt != var_table.cend();
	}

	/// add name value to a vector of Variables
	double Symbol_Table::declare(const std::string& s, const double d, const bool set_const)
	{
		if(is_declared(s)) ppp::error(s, " declared twice");
		var_table.push_back(Variable{s, d, set_const});
		return d;
	}
}  // ppp_calc
