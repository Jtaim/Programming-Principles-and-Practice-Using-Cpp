#ifndef SYMBOL_TABLE_H	// begin header guard
#define SYMBOL_TABLE_H

#include <string>
#include <vector>

namespace calculator
{
    class Symbol_Table
    {
    public:
        Symbol_Table();
        ~Symbol_Table();

        double get_value(const std::string &s);
        void set_value(const std::string &s, const double d);
        bool is_declared(const std::string &s);
        double declare(const std::string &s, const double d);

    private:
        // place to hold variable name value
        struct Variable {
            std::string name;
            double value{};
        };

        // container for all the variables
        std::vector<Variable> var_table;

        // helper template function to find name in var_table
        template<typename InputIt, typename T>
        constexpr InputIt find_value(InputIt first, InputIt last, const T &value)
        {
            for (; first != last; ++first) {
                if (first->name == value) {
                    return first;
                }
            }
            return last;
        }
    };
}

#endif	// close header guard
