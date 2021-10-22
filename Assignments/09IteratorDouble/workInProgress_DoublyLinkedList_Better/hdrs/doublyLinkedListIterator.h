#ifndef DOUBLY_LINKED_LIST_ITERATOR_CLASS_H
#define DOUBLY_LINKED_LIST_ITERATOR_CLASS_H

#include "Node.h"

template<typename E>
class DoublyLinkedListIterator
{
public:
    /*****************************
    ** CONSTRUCTOR & DESTRUCTOR **
    *****************************/
    DoublyLinkedListIterator(void);
    DoublyLinkedListIterator(Node<E> *ptr);

    /*************
    ** MUTATORS **
    *************/
    DoublyLinkedListIterator<E>& operator++(void);
    DoublyLinkedListIterator<E> operator++(int);
    DoublyLinkedListIterator<E>& operator--(void);
    DoublyLinkedListIterator<E> operator--(int);
    E& operator*(void);
    
    /**************
    ** ACCESSORS **
    **************/
    const E& operator*(void) const;
    const E& operator->(void) const;
    bool operator==(const DoublyLinkedListIterator<E>& that) const;
    bool operator!=(const DoublyLinkedListIterator<E>& that) const;

private:
    Node<E>* current;   //PROC - node poiter from a IntList object.
};

#include "doublyLinkedListIterator.cpp"

#endif //DOUBLY_LINKED_LIST_ITERATOR_CLASS_H