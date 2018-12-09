#ifndef SYMBOL_TABLE_H	// begin header guard
#define SYMBOL_TABLE_H

#include <string>
#include <vector>

namespace calculator
{
    /// place to hold variable name value
    struct Variable {
        std::string name;
        double value{};
    };

    class Symbol_Table
    {
    public:
        Symbol_Table();
        ~Symbol_Table();

        double get_value(const std::string s);
        void set_value(const std::string s, const double d);
        bool is_declared(const std::string s);
        double define_name(const std::string s, const double d);

    private:
        // container for all the variables
        std::vector<Variable> var_table;

        // overloaded equality operator to find name
        friend bool operator==(const calculator::Variable &v, const std::string &s);
        friend bool operator==(const std::string &s, const calculator::Variable &v);
    };
}

#endif	// close header guard
