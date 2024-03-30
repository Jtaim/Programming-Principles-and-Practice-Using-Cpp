/*
    Written by Jtaim
    Date 18 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 3
    Design and implement a Name_pairs class (name,age) pairs.
    - name is a vector<string>
    - age is a vector<double>
    - read_names() to read in a series of names
    - read_ages() to prompt user for an age for each name
    - operator<< to print name[i], age[i] pairs. One per line in the order determined by the name vector.
    - sort() to sort name vector is alphabetical order and reorganizes age vector to match.
    - operator==
    - operator!=

    Implement all operations as members functions.
    Test the class.
*/

#include"../includes/ppp.hpp"

class Name_pairs
{
public:
    void read_names();
    void read_ages();
    void sort();
    friend std::ostream& operator<<( std::ostream& os, const Name_pairs& np );
    friend bool operator==( const Name_pairs& np1, const Name_pairs& np2 );
    friend bool operator!=( const Name_pairs& np1, const Name_pairs& np2 );

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

std::ostream& operator<<( std::ostream& os, const Name_pairs& np )
{
    // Since operator<< is a friend of the Name_pairs class, we can access Name_pairs members directly.
    if( np.m_names.size() == np.m_ages.size() )
    {
        for( auto itr{ np.m_names.begin() }; itr < np.m_names.cend(); ++itr )
        {
            std::size_t index = static_cast<std::size_t>( itr - np.m_names.begin() );
            os << np.m_names.at( index ) << " is " << np.m_ages.at( index ) << " years old.\n";
        }
    }
    else
    {
        ppp::error( "vector sizes do not match!" );
    }
    return os;
}

bool operator==( const Name_pairs& np1, const Name_pairs& np2 )
{
    return np1.m_names == np2.m_names && np1.m_ages == np2.m_ages;
}

bool operator!=( const Name_pairs& np1, const Name_pairs& np2 )
{
    return !( np1 == np2 );
}


int main()
try
{
    Name_pairs np;
    np.read_names();
    np.read_ages();
    Name_pairs copy_np{ np };

    if( np == copy_np )
    {
        std::cout << "np == copy_np\n";
    }
    else if( np != copy_np )
    {
        std::cout << "np != copy_np\n";
    }
    std::cout << "np:\n" << np << "\n";
    std::cout << "copy_np:\n" << copy_np << "\n";

    np.sort();
    if( np == copy_np )
    {
        std::cout << "np == copy_np\n";
    }
    else if( np != copy_np )
    {
        std::cout << "np != copy_np\n";
    }
    std::cout << "np:\n" << np << "\n";
    std::cout << "copy_np:\n" << copy_np << "\n";

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