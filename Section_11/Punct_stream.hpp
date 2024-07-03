#pragma once

#include <iostream>
#include <sstream>
#include <string>

class Punct_stream
{
public:
    Punct_stream( std::istream &is )
        : source{ is }, sensitive{ true }
    {}

    void whitespace( const std::string &s ) { white = s; }  // makes the whitespace set
    void add_white( char c ) { white += c; }                // add to whitespace set
    bool is_whitespace( char c ) const;                     // is c in the whitespace set
    void case_sensitive( bool b ) { sensitive = b; }
    bool is_case_sensitive() const { return sensitive; }

    Punct_stream& operator>>( std::string &s );
    operator bool();
    //std::string contraction_check( std::string &s );

private:
    std::istream &source;       // character source
    std::istringstream buffer;  // we let buffer do our formatting
    std::string white;          // characters considered “whitespace”
    bool sensitive;             // is the stream case-sensitive?};
};
