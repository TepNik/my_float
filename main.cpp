#include <iostream>
#include "fraction.h"

int main()
{
    tnik::fraction x(0.3), y(3, 10);
    std::cout << x << ' ' << y << ' ' << (x == y) << '\n';
    return 0;
}