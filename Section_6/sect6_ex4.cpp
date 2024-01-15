//written by Jtaim
//date 9 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 6 exercise 4
Rewrite Section 4 exercise 19 with a class Name_value with a string and value object.
Use a vector<Name_value> instead of 2 vectors.
A program where you first enter a set of name-and-value pairs, such as Joe 17 and Barbara 22.
For each pair, add the name to a vector called names and the number to a vector called scores
(in corresponding positions, so that if names[7]=="Joe" then scores[7]==17).
Terminate input with NoName 0.
Check that each name is unique and terminated with an error message if a name is entered twice.
Write out all the (name, score) pairs, one per line.
*/

#include "section6.hpp"

struct NameValue
{
    bool operator==( const NameValue& nv );
    bool operator!=( const NameValue& nv );
    friend std::istream& operator>>( std::istream& is, NameValue& nv );
    friend std::ostream& operator<<( std::ostream& os, const NameValue& nv );
    std::string name;
    double score;
};

bool NameValue::operator==( const NameValue& nv )
{
    return this->name == nv.name && this->score == nv.score;
}

bool NameValue::operator!=( const NameValue& nv )
{
    return !( *this == nv );
}

std::istream& operator>>( std::istream& is, NameValue& nv )
{
    is >> nv.name >> nv.score;
    if( !is.good() && !is.eof() )
    {
        error( "Data input failure" );
    }

    std::transform( nv.name.begin(), nv.name.end(), nv.name.begin(),
                    []( unsigned char c ) { return narrow_cast<char>( ::tolower( c ) ); } );

    return is;
}

std::ostream& operator<<( std::ostream& os, const NameValue& nv )
{
    os << "name: " << nv.name << "\tscore: " << nv.score;
    return os;
}


const NameValue termination{ "noname", 0 };

int main()
{
    using namespace std;

    try
    {
        vector<NameValue> ranks;
        cout << "Enter names and scores. Terminate input with \"NoName 0\"\n";
        // collect valid data
        for( NameValue nv; cin >> nv && nv != termination;)
        {
            // check if duplicated
            if( ranks.cend() != std::find_if( ranks.cbegin(), ranks.cend(),
                [&nv]( const auto& ns ) { return ns.name == nv.name; } ) )
            {
                error( "found a duplicated name" );
            }

            ranks.push_back( { nv.name, nv.score } );
        }

        // print contents to screen
        if( ranks.empty() )
        {
            std::cout << "nothing entered\n";
        }
        else
        {
            // print contents to screen
            for( const auto& i : ranks )
            {
                std::cout << i << std::endl;
            }
        }
    }
    catch( std::exception& e )
    {
        std::cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch( ... )
    {
        std::cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }

    keep_window_open();
    return 0;
}
