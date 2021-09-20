#ifndef DOUBLY_LINKED_LIST_CLASS_H
#define DOUBLY_LINKED_LIST_CLASS_H

#include "Node.h"
#include <iostream>

template<typename E>
class DoublyLinkedList
{
public:
    /*****************************
    ** CONSTRUCTOR & DESTRUCTOR **
    *****************************/
    DoublyLinkedList(void);
    DoublyLinkedList(const DoublyLinkedList<E> &that);
    DoublyLinkedList& operator=(const DoublyLinkedList<E> &that);
    ~DoublyLinkedList(void);

    /**************
    ** ACCESSORS **
    **************/
    void display(std::ostream& out = std::cout, bool forward = true) const;
    const E& front(void) const;
    const E& back(void) const;
    std::size_t size(void) const;
    bool isEmpty(void) const;
    bool isInList(const E& target) const;

    /*************
    ** MUTATORS **
    *************/
    void push_front(int value);
    void pop_front(void);
    void push_back(const E& value);
    void pop_back(void);
    bool remove_all_targets(const E& target);
    bool remove_first_target_instance(const E& target);
    void clear(void);

private:
    std::size_t numberOfNodes;
    Node<E>* head;
    Node<E>* tail;
};

template<typename E>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<E>& doubly_linsked_list);

#include "doublyLinkedList.cpp"
#endif //DOUBLY_LINKED_LIST_CLASS_H