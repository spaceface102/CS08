#include "polynomial.h"
#include <iostream>

int main(void)
{
    Polynomial f = {1, 2, 3, 4};
    Polynomial g = {{3.4, 2.0}, {32, 0}, {99.67, 9}};
    Polynomial k = {4, 5, 6};
    Polynomial fk;

    std::cout << "f(x) = " << f << "\n";
    std::cout << "g(x) = " << g << "\n";
    std::cout << "k(x) = " << k << "\n";
    std::cout << "f(x) + k(x) = fk(x) = " << (fk = std::move(f + k)) << "\n";

    std::cout << "f(42) = " << f(42) << "\n";
    std::cout << "g(42) = " << g(42) << "\n";
    std::cout << "k(42) = " << k(42) << "\n";
    std::cout << "fk(42) = " << fk(42) << "\n";
    std::cout << "(g(x) + fk(x))(10) = " << (g + fk)(10) << "\n";
    return 0;
}