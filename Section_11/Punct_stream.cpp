#include "Punct_stream.hpp"
#include <algorithm>

bool Punct_stream::is_whitespace( const char c ) const
{
    if( !white.empty() )
    {
        return ( white.find( c ) != std::string::npos ) ? true : false;
    }
    else
    {
        auto ch = static_cast<unsigned char>( c );
        return ch != '\'' && std::ispunct( ch ) != 0 || std::isdigit( ch ) != 0;
    }
}

Punct_stream &Punct_stream::operator>>( std::string &s )
{
    while( !( buffer >> s ) )       // try to read from buffer
    {
        if( buffer.bad() || !source.good() )
        {
            return *this;
        }
        buffer.clear();

        std::string line;
        getline( source, line );    // get a line from source

        // do character replacement as needed:
        for( char &ch : line )
        {
            if( is_whitespace( ch ) )
            {
                ch = ' ';
            }
            else if( !sensitive )
            {
                ch = static_cast<char>( std::tolower( static_cast<unsigned char>( ch ) ) );
            }
        }
        buffer.str( line );
    }
    return *this;
}

Punct_stream::operator bool()
{
    return !( source.fail() || source.bad() ) && buffer.good();
}
