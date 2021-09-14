#include "bag.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void)
{
    std::srand(std::time(NULL));

    Bag<int> hello;
    for (int i = 0; i < 20; i++)
        hello.insert(std::rand()%10);

    int randomNum = std::rand()%10;

    std::cout << "Original: " << hello << "\n";
    hello.erase(randomNum);
    std::cout << "Target:   " << randomNum << "\n";
    std::cout << "Erased:   " << hello << "\n";

    std::cout << "\n";

    Bag<double> tester0;
    Bag<double> tester1;
    tester1.insert(42069);
    for (int i = 0; i < 10; i++)
        tester0.insert(42), tester1.insert(42);
    
    Bag<double> tester2 = tester0;
    Bag<double> tester3 = tester1;
    tester2.insert(42069);
    tester3.insert(42069);

    std::cout
    << tester0 << "\n"
    << tester1 << "\n"
    << tester2 << "\n"
    << tester3 << "\n";

    tester0.erase(42);
    tester1.erase(42);
    tester2.erase(42);
    tester3.erase(42);

    std::cout
    << tester0 << "\n"
    << tester1 << "\n"
    << tester2 << "\n"
    << tester3 << "\n";
    return 0;
}