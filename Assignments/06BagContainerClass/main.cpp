#include "bag.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(void)
{
    std::srand(std::time(nullptr));
    const int MAX_SIZE = std::rand()%16;
    const int MAX_VALUE = std::rand()%41;
    const int TARGET_TO_REMOVE = std::rand()%(MAX_VALUE + 1);

    Bag<int> a_bag;
    for (int i = 0; i < MAX_SIZE; i++)
        a_bag.insert(std::rand()%(MAX_VALUE + 1));

    std::cout << "Number of items in a_bag: " << a_bag.getSize() << "\n";
    std::cout << ((a_bag.isEmpty()) ? "The bag is empty" : "The bag is NOT empty") << "\n\n";

    if (a_bag.getSize() != 0)
    {
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "Removing first occurrence of " << TARGET_TO_REMOVE << ":\n"; 
        a_bag.erase_one(TARGET_TO_REMOVE);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "Removing ALL occurrence of " << TARGET_TO_REMOVE << ":\n"; 
        a_bag.erase(TARGET_TO_REMOVE);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";
    }

    if (a_bag.getSize())
    {
        int rand_index = std::rand()%(a_bag.getSize());
        std::cout << "Removing first occurrence of " << a_bag[rand_index] << ":\n"; 
        a_bag.erase_one(a_bag[rand_index]);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
    }

    //check since size of bag might be 1
    if (a_bag.getSize() != 0)
    {
        int rand_index = std::rand()%(a_bag.getSize());
        std::cout << "Removing ALL occurrence of " << a_bag[rand_index] << ":\n"; 
        a_bag.erase(a_bag[rand_index]);
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";

        std::cout << "Removing all the elements in the bag\n";
        a_bag.clear();
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";
    }

    if (MAX_SIZE != 0)
    {
        std::cout << "Refilling the bag...\n";
        for (int i = 0; i < MAX_SIZE; i++)
            a_bag.insert(std::rand()%(MAX_VALUE + 1));

        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "a_bag = a_bag\n"; a_bag = a_bag;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "a_bag += a_bag\n"; a_bag += a_bag;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
        std::cout << "a_bag + a_bag\n"; a_bag + a_bag;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n\n";
    }

    if (a_bag.getSize())
    {
        const int rand_index = std::rand()%a_bag.getSize();
        const int rand_value = std::rand()%(MAX_VALUE + 1);

        std::cout
            << "Number of " << rand_value << "'s in the bag: " << a_bag.count(rand_value)
            << "\nNumber of " << a_bag[rand_index] << "'s in the bag: " << a_bag.count(a_bag[rand_index])
            << "\nModified value at index# " << rand_index << "\n";
        a_bag[rand_index] = 42424242;
        std::cout << "These are the bag's contents: \n" << a_bag << "\n";
    }

    //testing on empty bag
    Bag<double> empty_bag;

    std::cout << "\nTesting all methods on empty bag, look at code.\n";
    empty_bag.clear();
    empty_bag.full_clear();
    empty_bag.full_clear(); //just to prove can do double full_clear
    empty_bag.count(42.0);
    empty_bag.erase_one(42.0);
    empty_bag.erase(42.0);
    empty_bag.getCapacity();
    empty_bag.getSize();
    empty_bag.isEmpty();
    empty_bag.insert(42.0); //insert just to delete
    empty_bag.count(42.0);
    empty_bag.erase_one(42.0);
    empty_bag.erase(42.0);
    empty_bag.getCapacity();
    empty_bag.getSize();
    empty_bag.isEmpty();
    std::cout << "If no weird errors, everything worked!\n";

    return 0;
}