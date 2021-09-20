#ifndef NODE_STRUCT_H
#define NODE_STRUCT_H

template<typename E>
struct Node
{
    int data;
    Node<E>* next;
    Node<E>* prev;
    Node(const E& data) : data(data), next(nullptr), prev(nullptr) {}
};

#endif //NODE_STRUCT_H