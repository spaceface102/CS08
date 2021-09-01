#include "myVector.h"
#include <iostream>

int main(void)
{
    IntVector vect;

    for (int i = 0; i < 10; i++)
        vect.add(i);

    for (unsigned long i = 0; i < vect.size(); i++)
        std::cout << vect.get(i); //prints 0123456789

    return 0;
}