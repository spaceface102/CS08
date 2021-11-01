#include <SFML/Graphics.hpp>
#include <iostream>
#include "KeyboardShortcuts_Handler.h"

int main(void)
{
    while (!KeyShortcuts::isUndo()) {}
    std::cout << "Was able to hit that mofo!!!\n";
    return 0;
}