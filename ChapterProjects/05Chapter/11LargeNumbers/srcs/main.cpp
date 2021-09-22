#include <iostream>
#include "bigNumber.h"

int main(void)
{
    typedef BigNumber<10> Base10;

    Base10 x{1, 0, 2, 3};
    Base10 y{9, 9};
    
    std::cout << x + y << "\n";
    std::cout << y + x << "\n";
    std::cout << x - y << "\n";
    std::cout << y - x << "\n";
    std::cout << x*y << "\n";
    std::cout << y*x << "\n";
    std::cout << y/x << "\n";
    std::cout << x/y << "\n";
    std::cout << x%y << "\n";
    std::cout << y%x << "\n";
    std::cout << (x << Base10{1}) << "\n";
    std::cout << (x >> Base10{1}) << "\n";
    std::cout << (1023 >> 1) << "\n";

    std::cout << (x > y) << "\n";    
    std::cout << (x >= y) << "\n";    
    std::cout << (x <= y) << "\n";    
    std::cout << (x < y) << "\n";    
    std::cout << (x == y) << "\n";    
    std::cout << (x != y) << "\n";    
    return 0;
}