#include "polynomial.h"
#include <iostream>

int main(void)
{
    Polynomial f = {1, 2, 3, 4};
    Polynomial g = {{3.4, 2.0}, {32, 0}, {99.67, 9}};
    Polynomial k;

    std::cout << k << "\n";
    std::cout << "f(x) = " << f << "\n";
    std::cout << "g(x) = " << g << "\n";
    std::cout << "Sort:\n";
    f.sort(); g.sort();
    std::cout << "f(x) = " << f << "\n";
    std::cout << "g(x) = " << g << "\n";
    std::cout << "f(42) = " << f(42) << "\n";
    std::cout << "g(42) = " << g(42) << "\n";

    return 0;
}