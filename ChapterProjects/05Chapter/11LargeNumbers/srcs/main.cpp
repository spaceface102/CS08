#include <iostream>
#include "bigNumber.h"
#include <cstdlib>
#include <ctime>

int main(void)
{
    {
        typedef BigNumber<10> Base10;

        Base10 x{1, 0, 2, 3};
        Base10 y = 99;
        
        std::cout << "x = " << x << "\n";
        std::cout << "y = " << y << "\n";
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
        std::cout << (x >> Base10{1}) << "\n\n";

        std::cout << (x > y) << "\n";
        std::cout << (x >= y) << "\n";
        std::cout << (x <= y) << "\n";
        std::cout << (x < y) << "\n";
        std::cout << (x == y) << "\n";
        std::cout << (x != y) << "\n";
    }

    {
        BigNumber<1000> x = {24, 5};
        BigNumber<1000> y = 99;

        std::cout << "x = " << x << "\n";
        std::cout << "y = " << y << "\n";
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
        std::cout << (x << BigNumber<1000>{1}) << "\n";
        std::cout << (x >> BigNumber<1000>{1}) << "\n\n";

        std::cout << (x > y) << "\n";
        std::cout << (x >= y) << "\n";
        std::cout << (x <= y) << "\n";
        std::cout << (x < y) << "\n";
        std::cout << (x == y) << "\n";
        std::cout << (x != y) << "\n";
    }

    return 0;
}