/*
    Written by Jtaim
    Sept 8 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Exercise 9
    Write a program that takes two files containing sorted whitespace-separated words and merges them, preserving order.
*/

#include "../includes/ppp.hpp"

constexpr std::array<std::string_view, 2> ws_sep_word_files{
    "sect10_ex9a.txt",
    "sect10_ex9b.txt"
};

constexpr std::string_view combined_files{ "sect10_ex9.txt" };

int main()
try
{
    // setup the files to capture whitespace-separated words
    for( const std::string_view fn : ws_sep_word_files )
    {
        std::ofstream fout( fn.data() );
        if( !fout )
        {
            ppp::error( "failed to open ", fn.data() );
        }
        std::cout << "Enter some white spaced strings into file "
            << fn << ". EOF to exit(ctrl-z)!\n";
        for( std::string s; std::cin >> s && fout; )
        {
            fout << s << " ";
        }
        if( fout.fail() )
        {
            ppp::error( "failed to enter white spaced strings into file" );
        }
        std::cin.clear();	// clear eof
        fout.close();
    }

    std::ofstream fout{ combined_files.data() };
    if( !fout )
    {
        ppp::error( "could not open ", combined_files.data() );
    }

    for( const std::string_view fn : ws_sep_word_files )
    {
        std::ifstream fin{ fn.data() };
        if( !fin )
        {
            ppp::error( "could not open ", fn.data() );
        }
        for( std::string data; fin >> data;)
        {
            fout << data << " ";
        }
        if( !fin.eof() )
        {
            ppp::error( "file not completely copied" );
        }
        fout << "\n";
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::cerr << R"(exception: )" << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << R"(exception)";
    ppp::keep_window_open();
    return 2;
}
