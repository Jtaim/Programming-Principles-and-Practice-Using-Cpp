#include "../includes/ppp.hpp"

void swap_v( int a, int b )
{
    int temp{ a };
    a = b;
    b = temp;
    std::cout << std::format( "*** In function swap_v() a: {} b: \n", a, b );
}

void swap_r( int& a, int& b )
{
    int temp{ a };
    a = b;
    b = temp;
    std::cout << std::format( "*** In function swap_r() a: {} b: \n", a, b );
}

// cannot assign to a variable that is const
//void swap_cr(const int &a, const int &b)
//{
//    int temp{a};
//    a = b;
//    b = temp;
//}

int main()
{
    int x{ 7 };
    int y{ 9 };
    std::cout << std::format( "x: {} y: {}\n", x, y );
    swap_v( x, y );
    std::cout << std::format( "after swap_v() x: {} y: {}\n", x, y );
    swap_r( x, y );
    std::cout << std::format( "after swap_r() x: {} y: {}\n", x, y );
    //swap_cr(x, y);    // cannot swap constants
    std::cout << std::format( "{:->50}", '\n' );

    swap_v( 7, 9 );     // dumb swap temp memory for 7 and 9 is lost
    //swap_r(7, 9);     // cannot swap literals
    //swap_cr(7, 9);    // cannot swap constants
    std::cout << std::format( "{:->50}", '\n' );

    const int cx{ 7 };
    const int cy{ 9 };
    std::cout << std::format( "x: {} y: {}\n", cx, cy );
    swap_v( cx, cy );
    std::cout << std::format( "after swap_v() x: {} y: {}\n", cx, cy );
    //swap_r(cx, cy);   // cannot convert from 'const int' to 'int &
    //swap_cr(cx, cy);  // cannot swap constants
    std::cout << std::format( "{:->50}", '\n' );

    double dx{ 7.7 };
    double dy{ 9.9 };
    std::cout << std::format( "x: {} y: {}\n", dx, dy );
    swap_v( dx, dy );   // truncates double to covert to int
    std::cout << std::format( "after swap_v() x: {} y: {}\n", dx, dy );
    //swap_r(dx, dy);   // cannot convert from 'double' to 'int &'
    //swap_cr(dx, dy);  // cannot swap constants
    std::cout << std::format( "{:->50}", '\n' );

    swap_v( 7.7, 9.9 ); // truncates double to covert to int, plus temp memory for 7.7 and 9.9 is lost
    //swap_r(7.7, 9.9); // cannot convert from 'double' to 'int &'
    //swap_cr(7.7, 9.9);// cannot swap constants
    std::cout << std::format( "{:->50}", '\n' );

    ppp::keep_window_open();
    return 0;
}
