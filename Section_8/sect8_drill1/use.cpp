#include "my.h"

#include <iostream>

int main()
{
    extern int foo;
    foo = 7;
    print_foo();
    print(99);

    char cc;
    std::cin >> cc;
    return 0;
}