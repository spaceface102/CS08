#include "palindrome.h"

bool isPalindrome(const std::string& str)
{
    return isPalindrome(str.c_str(), str.size());
}
//EOF

bool isPalindrome(const char* str, unsigned long size)
{
    const char* begin;  //PROC - point to first char in str
    const char* end;    //PROC - point to last char in str

    begin = str;
    end = str + size - 1;

    //starting address will always be smaller than
    //ending address, unless size = 1, in which case
    //auto isPalindrome = true
    while (begin < end)
    {
        //allows for sentences to be palindromes
        if (*begin == ' ')
        {
            begin++;
            continue; //forces check of begin < end
        }
        else if (*end == ' ')
        {
            end--;
            continue; //again, this forces the while loop check
        }

        //core checking logic for palindrome
        if (*begin != *end)
            return false;

        //get ready for the next iteration
        begin++;
        end--;
    }

    return true;
}
//EOF