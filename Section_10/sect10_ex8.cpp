/*
    Written by Jtaim
    April 13 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Exercise 8
    Write a program that accepts two file names and produces a new file that is the contents of the first
    file followed by the contents of the second; that is, the program concatenates the two files.

    the files I used are the input and output text files from exercise 5
*/

#include "../includes/ppp.hpp"

constexpr std::array<std::string_view, 2> read_files{
    "sect10_ex5_in.txt",
    "sect10_ex5_out.txt"
};

constexpr std::string_view combined_files{ "sect10_ex8.txt" };

int main()
try
{
    // setup the file to capture read files
    std::ofstream fout{ combined_files.data() };
    if( !fout )
    {
        ppp::error( "could not open ", combined_files.data() );
    }

    for( const auto fn : read_files )
    {
        fout << "Contents of file " << fn << "\n";
        std::ifstream fin{ fn.data() };
        if( !fin )
        {
            ppp::error( "could not open ", fn.data() );
        }
        for( std::string data; std::getline( fin, data );)
        {
            fout << data << "\n";
        }
        if( !fin.eof() )
        {
            ppp::error( "file not completely copied" );
        }
        fout << "\n";
    }
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
