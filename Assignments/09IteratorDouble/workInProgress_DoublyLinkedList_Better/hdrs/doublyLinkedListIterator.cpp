#ifndef DOUBLY_LINKED_LIST_ITERATOR_CLASS_CPP
#define DOUBLY_LINKED_LIST_ITERATOR_CLASS_CPP

#include "doublyLinkedListIterator.h"

template<typename E>
DoublyLinkedListIterator<E>::DoublyLinkedListIterator(Node<E>* const& ptr) 
    : current_indirect(&ptr) 
{}
//EOF

template<typename E>
E& DoublyLinkedListIterator<E>::operator*(void)
{
    return (*current_indirect)->data;
}
//EOF

template<typename E>
DoublyLinkedListIterator<E>& DoublyLinkedListIterator<E>::operator++(void)
{
    current_indirect = &((*current_indirect)->next);
    return *this;
}
//EOF

template<typename E>
DoublyLinkedListIterator<E> DoublyLinkedListIterator<E>::operator++(int)
{
    DoublyLinkedListIterator<E> result = *this;
    current = current->next;
    return result;
}
//EOF

template<typename E>
DoublyLinkedListIterator<E>& DoublyLinkedListIterator<E>::operator--(void)
{
    current = current->prev;
    return *this;
}
//EOF

template<typename E>
DoublyLinkedListIterator<E> DoublyLinkedListIterator<E>::operator--(int)
{
    DoublyLinkedListIterator<E> result = *this;
    current = current->prev;
    return result;
}
//EOF

template<typename E>
const E& DoublyLinkedListIterator<E>::operator*(void) const
    {return current->data;}
//EOF

template<typename E>
const E& DoublyLinkedListIterator<E>::operator->(void) const
    {return current->data;}
//EOF

template<typename E>
bool DoublyLinkedListIterator<E>::operator==(const DoublyLinkedListIterator& that) const
    {return (this->current == that.current);}
//EOF

template<typename E>
bool DoublyLinkedListIterator<E>::operator!=(const DoublyLinkedListIterator& that) const
    {return !(*this == that);}
//EOF

#endif //DOUBLY_LINKED_LIST_ITERATOR_CLASS_CPP