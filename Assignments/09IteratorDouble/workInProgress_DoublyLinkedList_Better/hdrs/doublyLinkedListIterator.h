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
    DoublyLinkedListIterator(Node<E>* const& ptr);

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
    Node<E>* const* current_indirect;   //pointer to a constant pointer to a Node

    /*
     * The whole reason for having an indirect pointer to a Node
     * is really for just the case when tail or head change due
     * to a push_back, pop_back, push_front, pop_front operation.
     * Since I have a pointer to head or tail (and not to just a 
     * a shared pointer to what head or tail points to), if they
     * temselves change, aka they start pointing to a different Node,
     * the indirect pointer will not care; it's not pointing to some
     * random node but instead to the thing that points to it.
     * 
     * current_idirect is defined as Node<E>* const* (aka a pointer
     * tp a constant pointer, pointing to a Node<E>) because I want
     * to send out the message that the passed in tail or head will
     * not be changed, and the iterator will not randomly change what
     * they temselves point to; though the contents of the Node itself
     * is still allowed to be modified.
     * 
     * Actually under close inspection, this too will fail. This is
     * due to the fact that iterators need to move forward, and due
     * to the how double pointers work, we will not be pointing to the
     * next node but the next pointer of the previous node. Derefencing
     * this will have unspecified consequences. This thing is more
     * tough than I first though....
    */
};

#include "doublyLinkedListIterator.cpp"

#endif //DOUBLY_LINKED_LIST_ITERATOR_CLASS_H