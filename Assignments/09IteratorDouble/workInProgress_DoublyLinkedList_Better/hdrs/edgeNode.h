#ifndef EDGE_NODE_STRUCT_H
#define EDGE_NODE_STRUCT_H

#include "Node.h"

template<typename E>
struct EdgeNode
{
    Node<E>** head_ptr;
    Node<E>** tail_ptr;
    //update only when begin or end is called 
    //on linked list, OR when constructing list obj
    //OR destructing/clearing
    Node<E> interface_node;

    EdgeNode(void) = delete;
    EdgeNode(Node<E>*& head, Node<E>*& tail)
        : head_ptr(&head), tail_ptr(&tail)
    {}
};

#endif //EDGE_NODE_STRUCT_H