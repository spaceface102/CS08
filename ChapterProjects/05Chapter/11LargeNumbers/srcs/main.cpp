#include <iostream>
#include "bigNumber.h"

int main(void)
{
    BigNumber<16> test = {15, 15};
    BigNumber<16> test2 = {9};

    std::cout << (test & test2) << "\n";
    printf("%x\n", (0xFF & 0x9));
    return 0;
}