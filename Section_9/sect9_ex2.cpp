/*
    Written by Jtaim
    Date 15 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 2
    Design and implement a Name_pairs class (name,age) pairs.
    - name is a vector<string>
    - age is a vector<double>
    - read_names() to read in a series of names
    - read_ages() to prompt user for an age for each name
    - print() to print name[i], age[i] pairs. One per line in the order determined by the name vector.
    - sort() to sort name vector is alphabetical order and reorganizes age vector to match.

    Implement all operations as members functions.
    Test the class.
*/

#include"../includes/ppp.hpp"

class Name_pairs
{
public:
    void read_names();
    void read_ages();
    void print() const;
    void sort();

private:
    std::vector<std::string> m_names;
    std::vector<double> m_ages;
};

void Name_pairs::read_names()
{
    std::cout << "Enter names separated by ',' or new line. EOF (ctrl z) to exit.\n";
    char c{};
    std::string name;
    while( std::cin.get( c ) )
    {
        if( c != ',' && c != '\n' )
        {
            if( !name.empty() )
            {
                name += c;
            }
            else if( c != ' ' )
            {
                name += c;
            }
        }
        else if( !name.empty() )
        {
            m_names.push_back( name );
            name.clear();
        }
    }
    if( std::cin.eof() )
    {
        std::cin.clear();   // clear EOF
    }
}

void Name_pairs::read_ages()
{
    for( const auto& n : m_names )
    {
        std::cout << "Enter age for " << n << ": ";
        double age{};
        while( true )
        {
            if( !( std::cin >> age ) )
            {
                std::cin.clear();
                std::cin.ignore( std::cin.rdbuf()->in_avail() );	//clear cin buffer
                std::cout << "Invalid age entered!\nRenter age for " << n << ": ";
            }
            else
            {
                m_ages.push_back( age );
                break;
            }
        }
    }
}

void Name_pairs::print() const
{
    std::cout << "\n\n";
    if( m_names.size() == m_ages.size() )
    {
        for( std::size_t index{}; index < m_names.size(); ++index )
        {
            std::cout << m_names.at( index ) << " is " << m_ages.at( index ) << " years old.\n";
        }
    }
    else
    {
        ppp::error( "vector sizes do not match!" );
    }
}

// string all lower case
std::string lower( const std::string& s )
{
    std::string low_string;
    for( auto c : s )
    {
        low_string += static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) );
    }
    return std::move( low_string );
}

void Name_pairs::sort()
{
    if( m_names.empty() || ( m_names.size() != m_ages.size() ) )
    {
        ppp::error( "vector sizes do not match!" );
    }

    for( std::size_t idx1{}; idx1 < m_names.size(); ++idx1 )                // name to compare
    {
        for( std::size_t idx2{ idx1 + 1 }; idx2 < m_names.size(); ++idx2 )  // compare with rest of names
        {
            auto str1{ lower( m_names.at( idx1 ) ) };                       // set to lower so sort keeps in alphabetically order
            auto str2{ lower( m_names.at( idx2 ) ) };
            if( str1 > str2 )                                               // sort from lowest to highest
            {
                // store greater element
                std::string temp_name = std::move( m_names.at( idx1 ) );
                double temp_age = m_ages.at( idx1 );
                // place lesser element at previous greater element
                m_names.at( idx1 ) = m_names.at( idx2 );
                m_ages.at( idx1 ) = m_ages.at( idx2 );
                // place greater in the previous lesser element
                m_names.at( idx2 ) = std::move( temp_name );
                m_ages.at( idx2 ) = temp_age;
            }
        }
    }
}


int main()
try
{
    Name_pairs np;
    np.read_names();
    np.read_ages();
    np.print();
    np.sort();
    np.print();

    ppp::keep_window_open();
    return 0;
}
catch( std::exception& e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}