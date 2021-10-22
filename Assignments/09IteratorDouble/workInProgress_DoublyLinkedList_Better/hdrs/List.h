#include "Node.h"

template<typename E>
class List
{
public:
    template<typename T>
    class Iterator
    {
    public:
        Iterator(void);
        Iterator(Node<E>* ptr);

        Iterator<T>& operator++(void);
        Iterator<T>& operator--(void);
        T& operator*(void);

        bool operator==(const Iterator<T>& that) const;
        bool operator!=(const Iterator<T>& that) const;
    
    private:
        Node<T>* current;
    };


public:
    List(void);
    List(const List<E>& that);
    List& operator=(const List& that);
    ~List(void);

    const E& front(void) const;
    const E& back(void) const;
    std::size_t size(void) const;
    bool isEmpty(void) const;

    E& front(void);
    E& back(void);
    const Iterator<E>&
    void push_front(const E& value);
    void pop_front(void);
    void push_back(const E& value);
    void pop_back(void);


private:
    Node<E>* head;
    Node<E>* tail;
    Node<E> fake_head;
    Node<E> fake_tail;
    Iterator<E> begin_iter;
    Iterator<E> end_iter;
};