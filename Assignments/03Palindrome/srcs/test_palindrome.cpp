#include "palindrome.h"
#include <string>
#include <iostream>

int main(void)
{
    std::string input_str;

    std::cout << "Please input a string: ";
    std::getline(std::cin, input_str);

    std::cout << input_str << " is "
    << (isPalindrome(input_str) ? "a" : "NOT a")
    << " Palindrome!\n";
    return 0;
}