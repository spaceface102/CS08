#include "bag.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(void)
{
    std::srand(std::time(nullptr));
#if 0
    const int MAX_LENGTH = std::rand()%16;
    const int MAX_SIZE = std::rand()%41;
    const int TARGET_TO_REMOVE = std::rand()%(MAX_SIZE + 1);

    Bag<int> a_bag;
    for (int i = 0; i < MAX_LENGTH; i++)
        a_bag.insert(std::rand()%(MAX_SIZE + 1));
#endif
    Bag<int> a_bag;

    const int MAX_LENGTH = 5;
    const int TARGET_TO_REMOVE = 1;
    a_bag.insert(6);
    a_bag.insert(2);
    a_bag.insert(0);
    a_bag.insert(2);
    a_bag.insert(4);
    a_bag.insert(4);

    std::cout << "Number of items in a_bag: " << a_bag.getSize() << "\n";
    std::cout << ((a_bag.isEmpty()) ? "The bag is empty" : "The bag is NOT empty") << "\n\n";

    if (MAX_LENGTH != 0)
    {
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "Removing first occurrence of " << TARGET_TO_REMOVE << ":\n"; 
        a_bag.erase_one(TARGET_TO_REMOVE);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "Removing ALL occurrence of " << TARGET_TO_REMOVE << ":\n"; 
        a_bag.erase(TARGET_TO_REMOVE);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";

        int rand_index = std::rand()%(a_bag.getSize());
        std::cout << "Removing first occurrence of " << 2 << ":\n"; 
        a_bag.erase_one(2);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        rand_index = std::rand()%(a_bag.getSize());
        std::cout << "Removing ALL occurrence of " << 4 << ":\n"; 
        a_bag.erase(4);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";

        std::cout << "Removing all the elements in the bag\n";
        a_bag.clear();
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";

#if 0
        std::cout << "Refilling the bag...\n";
        for (int i = 0; i < MAX_LENGTH; i++)
            a_bag.insert(std::rand()%(MAX_SIZE + 1));

        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "a_bag = a_bag\n"; a_bag = a_bag;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "a_bag += a_bag\n"; a_bag += a_bag;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "a_bag + a_bag\n"; a_bag + a_bag;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
#endif
}

    return 0;
}