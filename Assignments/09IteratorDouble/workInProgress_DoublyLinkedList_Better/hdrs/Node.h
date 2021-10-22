#ifndef NODE_STRUCT_H
#define NODE_STRUCT_H

template<typename E>
struct Node
{
    Node(const E& data) : data(data), next(nullptr), prev(nullptr) {}
    E data;
    Node<E>* next;
    Node<E>* prev;
};

#endif //NODE_STRUCT_H