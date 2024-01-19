#ifndef SYMBOL_TABLE_H	// begin header guard
#define SYMBOL_TABLE_H

#include <string>
#include <vector>

namespace calculator
{
    class Symbol_Table
    {
    public:
        double get_value( const std::string_view s );
        void set_value( const std::string_view s, const double d );
        bool is_declared( const std::string_view s );
        double declare( const std::string_view s, const double d, const bool set_const = false );

        Symbol_Table() = default;
        Symbol_Table( const Symbol_Table& st ) = delete;        // delete copy constructor    
        Symbol_Table( const Symbol_Table&& st ) = delete;       // delete move constructor
        Symbol_Table& operator=( Symbol_Table& st ) = delete;   // delete copy assignment operator
        Symbol_Table& operator=( Symbol_Table&& st ) = delete;  // delete move assignment operator

    private:
        // place to hold variable name value
        struct Variable
        {
            std::string name;
            double value{};
            bool is_const{ false };
        };

        // container for all the variables
        std::vector<Variable> var_table;

        // private function to find name in var_table
        using vt_itr = std::vector<Variable>::iterator;
        vt_itr find_name( vt_itr first, vt_itr last, const std::string_view value )
        {
            for( ; first != last; ++first )
            {
                if( first->name == value )
                {
                    return first;
                }
            }
            return last;
        }
    };
} // calculator

#endif	// close header guard
