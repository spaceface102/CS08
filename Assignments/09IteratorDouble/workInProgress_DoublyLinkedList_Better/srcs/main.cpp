#include "doublyLinkedList.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void)
{
    std::srand(std::time(nullptr));
    DoublyLinkedList<int> list;

    std::cout << "Displaying empty list: " << list << "\n";
    std::cout << "Testing basic insertion functions\n";
    list.push_back(43);             //insert at the at end of list
    std::cout << list << "\n";
    list.push_front(32);            //inster at the front of the list
    std::cout << list << "\n";
    list.insert_after(0, 7777);
    std::cout << list << "\n";
    list.insert_before(2, 5567);
    std::cout << list << "\n";

    std::cout << "\nOriginal size: " << list.size() << "\n";
    std::cout << "Original List: " << list << "\n";

    std::cout << "\nInserting random numbers...\n\n";
    const int max_value = (std::rand()%1000000) + 1;
    const std::size_t increase_size_by = (std::rand()%5) + 1;
    const int repeating_value = std::rand()%123456;

    for (std::size_t i = 0; i < increase_size_by; i++)
        list.push_back(std::rand()%max_value);

    for (std::size_t i = 0; i < increase_size_by; i++)
        list.insert_after(std::rand() % (list.size() - 1), repeating_value);

    std::cout << "New Size: " << list.size() << "\n";
    std::cout << "Modified List: " << list << "\n";
    std::cout << "list.isInList(" << repeating_value << ") = " << list.isInList(repeating_value) <<"\n";

    std::cout << "\nRemoving the first instance of " << repeating_value << "\n";
    list.remove_first_target_instance(repeating_value);
    std::cout << "New Size: " << list.size() << "\n";
    std::cout << "Modified List: " << list << "\n";
    std::cout << "list.isInList(" << repeating_value << ") = " << list.isInList(repeating_value) <<"\n";

    std::cout << "\nRemoving the ALL " << repeating_value << "'s in the list\n";
    list.remove_all_targets(repeating_value);
    std::cout << "New Size: " << list.size() << "\n";
    std::cout << "Modified List: " << list << "\n";
    std::cout << "list.isInList(" << repeating_value << ") = " << list.isInList(repeating_value) <<"\n";

    std::cout << "\nCopy constructing a new list...\n";
    DoublyLinkedList<int> list2{list};
    DoublyLinkedList<int> I_like_operators;

    std::cout << "Original List: " << list << "\n";
    std::cout << "Copied list  : " << list2 << "\n";

    std::cout << "Inserting random value in copied list....\n";
    list2.insert_after(std::rand() % (list2.size() - 1), std::rand()%max_value);
    std::cout << "Original List: " << list << "\n";
    std::cout << "Copied list  : " << list2 << "\n";

    std::cout << "\nCopying with overloaded assignment operator\n";
    I_like_operators = list2;
    std::cout << "Original List: " << list2 << "\n";
    std::cout << "Copied list  : " << I_like_operators << "\n";

    std::cout << "\nCopying again with smaller list using overloaded assignment operator\n";
    I_like_operators = list;
    std::cout << "Original List: " << list << "\n";
    std::cout << "Copied list  : " << I_like_operators << "\n";

    std::cout << "Inserting random value in copied list....\n";
    I_like_operators.insert_after(std::rand() % (I_like_operators.size() - 1), std::rand()%max_value);
    std::cout << "Original List: " << list << "\n";
    std::cout << "Copied list  : " << I_like_operators << "\n";

    std::cout << "\nJust for the fun of it, displaying original list backwayrds:\n";
    list.display(std::cout, false);
    std::cout << "\n";

    std::cout << "\n\n";

    DoublyLinkedList<float> helloList;
    
    std::cout << "Making new list...\n";
    for (std::size_t i = 0; i < 5; i++)
        helloList.push_back(std::rand()%20);
    
    std::cout << "Iterating over list using DoublyLinkedListIterator\n";
    for (DoublyLinkedListIterator<float> it = helloList.begin(); it != helloList.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "\nModifying random index with iterator\n";
    const std::size_t indexToModify = (std::rand())%(helloList.size() - 1) + 1;
    auto it = helloList.begin();
    
    for (std::size_t i = 0; i < indexToModify; ++it, ++i)   {}
    *it = rand()%1000;
    std::cout << "Modified index: " << indexToModify << "\n";
    std::cout << "List: " << helloList << "\n";

    --it;
    *it = rand()%100000;
    std::cout << "Modifying index (indexToModify - 1): " << indexToModify - 1 << "\n";
    std::cout << "List: " << helloList << "\n";

    std::cout << "Testing for range loop (need .begin and .end methods in class)\n";
    for (float node : helloList)
        std::cout << node << " ";
    std::cout << "\n";
    return 0;
}