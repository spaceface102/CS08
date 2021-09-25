#ifndef DOUBLY_LINKED_LIST_CLASS_CPP
#define DOUBLY_LINKED_LIST_CLASS_CPP

#include "doublyLinkedList.h"
#include <iostream>
#include <cassert>

/****************************************************************
 * 
 *  Method Constructor: Class DoublyLinkedList
 *  //DEFAULT CONSTRUCTOR
 * --------------------------------------------------------------
 *  Set both the head and tail pointer to nullptr
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must make an object, or call the constructor with no
 *      arguments.
 * 
 *  POST-CONDITIONS
 *      The object does not have any space to store anything
 *      yet. It is an empty list.
****************************************************************/
template<typename E>
DoublyLinkedList<E>::DoublyLinkedList(void)
    : head(nullptr), tail(nullptr), numberOfNodes(0),
      endNode(head, tail), beginNode(head, tail)
{
    setTailNext(numberOfNodes);
    setHeadPrev(numberOfNodes);
    updateBeginNode_Interface_Node(numberOfNodes);
    updateEndNode_Interface_Node(numberOfNodes);
}
//EOF

/****************************************************************
 * 
 *  Method Constructor: Class DoublyLinkedList
 *  //COPY CONSTRUCTOR
 * --------------------------------------------------------------
 * This is the overloaded copy constructor. It will copy all
 * the nodes of the passed in linked list, in the exact same 
 * order. The new object does not share any memory with the
 * passed in object.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The passed in DoublyLinkedList object can be in any stage, no
 *      node list, one node, list or more.
 * 
 *  POST-CONDITIONS
 *      If the passed in list is empty (no nodes), the new
 *      object's head and tail are both set to NULL. Else
 *      will traverse through the list, and make new nodes.
 *      All new memory is allocated on the heap, so deleting
 *      or modifying this new object will not have any affect
 *      on the object being used to make a copy out of.
****************************************************************/
template<typename E>
DoublyLinkedList<E>::DoublyLinkedList(const DoublyLinkedList& that)
    : endNode(head, tail), beginNode(head, tail)
{
    Node<E> *current_that;  //PROC - track node from "that"

    if (that.numberOfNodes == 0)
    {
        head = tail = nullptr; 
        numberOfNodes = 0;
    }
    else
    {
        current_that = that.head;
        head = tail = new Node<E>(current_that->data);
        numberOfNodes = that.numberOfNodes;

        current_that = current_that->next;
        while (current_that != &(that.endNode.interface_node))
        {
            tail->next = new Node<E>(current_that->data);
            tail->next->prev = tail;
            tail = tail->next;
            current_that = current_that->next;
        }
    }

    setTailNext(numberOfNodes);
    setHeadPrev(numberOfNodes);
    updateBeginNode_Interface_Node(numberOfNodes);
    updateEndNode_Interface_Node(numberOfNodes);
}
//EOF

/****************************************************************
 * 
 *  Method Destructor: Class DoublyLinkedList
 *  //DESTRUCTOR
 * --------------------------------------------------------------
 *  Free up the heap allocated memory allocated with the 
 *  DoublyLinkedList. "head" and "tail" are set to nullptr.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      DoublyLinkedList object must go out of scope, or delete must be
 *      called on an DoublyLinkedList pointer object.
 * 
 *  POST-CONDITIONS
 *      Any memory related with the list are no longer accessible.
****************************************************************/
template<typename E>
DoublyLinkedList<E>::~DoublyLinkedList(void)
{
    clear();
}
//EOF

/****************************************************************
 * 
 *  Method display: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Display all the values related to the list. If forward
 *  = true, will display from head to tail, else if forward
 *  = false, will display from tail to head.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The list can be filled or empty.
 *  POST-CONDITIONS
 *      The ouput will be sent to std::cout; all the output is
 *      on one line. No new line.
****************************************************************/
template<typename E>
void DoublyLinkedList<E>::display(std::ostream& out, bool forward) const
{
    Node<E> *current;       //PROC - keep track of current node in list
    Node<E> *terminating;   //PROC - the final node printed
    Node<E> *trueTerminate; //PROC - the actual termination node in list
    Node<E>* (*direction)(Node<E>* node);

    if (forward)
    {
        current = head;
        terminating = tail;
        trueTerminate = getTrueEndNode(numberOfNodes);
        direction = [](Node<E>* node) -> Node<E>* {return node->next;};
    }
    else
    {
        current = tail;
        terminating = head;
        getTrueBeginNode(numberOfNodes);
        direction = [](Node<E>* node) -> Node<E>* {return node->prev;};
    }

    while (current != terminating)
    {
        out << current->data << " ";
        current = direction(current);
    }
    if (terminating != trueTerminate)
        out << terminating->data;
}
//EOF


/****************************************************************
 * 
 *  Method front: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 * Return the value of associated with the head of the list.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call on a list of at least length 1 (at least one
 *      node).
 *  POST-CONDITIONS
 *      Assuming the calling object at least has one active node
 *      a copy of the value at the head will be returned. 
****************************************************************/
template<typename E>
const E& DoublyLinkedList<E>::front(void) const
{
    return beginNode.interface_node.data;
}
//EOF

/****************************************************************
 * 
 *  Method back: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 * Return the value of associated with the tail of the list.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call on a list of at least length 1 (at least one
 *      node).
 *  POST-CONDITIONS
 *      Assuming the calling object at least has one active node
 *      a copy of the value at the tail will be returned. 
****************************************************************/
template<typename E>
const E& DoublyLinkedList<E>::back(void) const
{
    return endNode.interface_node.data;
}
//EOF

template<typename E>
std::size_t DoublyLinkedList<E>::size(void) const
{
    return numberOfNodes;
}
//EOF

template<typename E>
bool DoublyLinkedList<E>::isEmpty(void) const
{
    return static_cast<bool>(numberOfNodes);
}
//EOF

template<typename E>
bool DoublyLinkedList<E>::isInList(const E& target) const
{
    Node<E>* current;
    bool targetIsInList;

    current = head;
    targetIsInList = false;
    while (current != getTrueEndNode(numberOfNodes) && !targetIsInList)
    {
        targetIsInList = (current->data == target);
        current = current->next;
    }

    return targetIsInList;
}
//EOF

/****************************************************************
 * 
 *  Method push_front: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Adds a new node in front of the head node. 
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The list can be filled or empty.
 *  POST-CONDITIONS
 *      If the list is empty, then both the head node and tail
 *      node are set to the new added node. Else, the a new head
 *      node is added.
****************************************************************/
template<typename E>
void DoublyLinkedList<E>::push_front(const E& value)
{
    if (numberOfNodes == 0)    //empty list
    {
        head = tail = new Node<E>(value);
        setTailNext(numberOfNodes + 1);
    }
    else
    {
        head->prev = new Node<E>(value);
        head->prev->next = head;
        head = head->prev;
    }

    numberOfNodes++;
    setHeadPrev(numberOfNodes);
}
//EOF

/****************************************************************
 * 
 *  Method push_back: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Adds a new node to the end of the list.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The list can be filled or empty.
 *  POST-CONDITIONS
 *      If the list is empty, head and tail will point to the
 *      same new node. Else, the tail before calling the method
 *      will now point to a new node.
****************************************************************/
template<typename E>
void DoublyLinkedList<E>::push_back(const E& value)
{
    if (numberOfNodes == 0)    //empty list
    {
        head = tail = new Node<E>(value);
        setHeadPrev(numberOfNodes + 1);
    }
    else
    {
        tail->next = new Node<E>(value);
        tail->next->prev = tail;
        tail = tail->next;
    }

    numberOfNodes++;
    setTailNext(numberOfNodes);
}
//EOF

template<typename E>
void DoublyLinkedList<E>::operator+=(const E& value)
{
    this->push_back(value);
}

/****************************************************************
 * 
 *  Method pop_front: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Deletes the front node.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The list can be filled or empty.
 *  POST-CONDITIONS
 *      If the list is empty, then nothing is done. Else
 *      current head is deleted, and the next node is made
 *      the new head.
****************************************************************/
template<typename E>
void DoublyLinkedList<E>::pop_front(void)
{
    //no node or single node. (nothing will happen
    //if we use delete on NULL, delete checks for that)
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
        //don't setHeadPrev() since head is nullptr
    }
    else
    {
        head = head->next;
        delete head->prev;
        setHeadPrev(numberOfNodes - 1);
    }

    numberOfNodes--;
}
//EOF

/****************************************************************
 * 
 *  Method pop_back: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Deletes the end node.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The list can be filled or empty.
 *  POST-CONDITIONS
 *      If the list is empty, then nothing is done. Else
 *      current tail is deleted, and the previous node is made
 *      the new tail.
****************************************************************/
template<typename E>
void DoublyLinkedList<E>::pop_back(void)
{
    //no node or single node. (nothing will happen
    //if we use delete on NULL, delete checks for that)
    if (head == tail)
    {
        delete tail;
        head = tail = nullptr;
        //don't setTailNext() since tail is nullptr
    }
    else
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        setTailNext(numberOfNodes - 1);
    }

    numberOfNodes--;
}
//EOF

template<typename E>
DoublyLinkedListIterator<E> DoublyLinkedList<E>::begin(void)
    {return DoublyLinkedList<E>{&endNode};}

//nodeIndex = 0 means head
//nodeIndex = list.size() - 1 OR numberOfNodes - 1 means tail
template<typename E>
void DoublyLinkedList<E>::insert_before(std::size_t nodeIndex, const E& value)
{
    assert("There are no nodes to even insert before!(Empty list)" && numberOfNodes > 0);
    assert("Use the push_front() method instead to set new head" && nodeIndex > 0);
    assert("Use the push_back() method to set new tail" && nodeIndex < numberOfNodes);

    std::size_t currentNodeIndex = 0;
    Node<E>* current = head;

    while (currentNodeIndex < nodeIndex - 1)
    {
        current = current->next;
        currentNodeIndex++;
    }
    
    //currentNodeIndex = nodeIndex - 1, aka the node before hand
    Node<E>* temp_next = current->next;
    current->next = new Node<E>(value);
    current->next->prev = current;
    current->next->next = temp_next;
    temp_next->prev = current->next;

    numberOfNodes++;
}
//EOF

//nodeIndex = 0 means head
//nodeIndex = list.size() - 1 mean tail
template<typename E>
void DoublyLinkedList<E>::insert_after(std::size_t nodeIndex, const E& value)
{
    assert("There are no nodes to even insert after!(Empty list)" && numberOfNodes > 0);
    assert("Use the push_back() method to set new tail" && nodeIndex < numberOfNodes - 1);
    this->insert_before(nodeIndex + 1, value);
}

/****************************************************************
 * 
 *  Method remove_duplicates: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Will delete every instance of the passed in the value from
 *  the list
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The list can be filled or empty. 
 *  POST-CONDITIONS
 *      The head is assured to change if the the node that head
 *      points to is the value being looked for. Note, head may change
 *      multiple times throughout the method.
 *      Tail can also change, but assuming it is a candinate for
 *      removal, will only be removed/changed once.
 *      Assuming the whole list is equal to the value passed in
 *      the finalized list will result in an empty list.
****************************************************************/
template<typename E>
bool DoublyLinkedList<E>::remove_all_targets(const E& value)
{
    Node<E> **current;   //PROC - track the current node indirectly
    Node<E> *removeNode; //PROC - temp while rewiring linked list
    bool removedValue;   //PROC - return value, true if a value is removed

    removedValue = false;
    current = &head;
    while (*current != tail)
    {
        if ((*current)->data == value)
        {
            //at most most removeNode = tail->prev
            removedValue = true;
            removeNode = *current;
            (*current)->next->prev = (*current)->prev;
            *current = (*current)->next;
            delete removeNode;

            numberOfNodes--;
        }
        else
            current = &((*current)->next);
    }

    if (tail == head)
    {
        if (numberOfNodes != 0 && tail->data == value)
        {   //single node with specified value
            removedValue = true;
            delete tail;
            head = tail = nullptr;
            numberOfNodes--;
        }
    }
    else if (tail->data == value) //linked list at least has two nodes.
    {
        removedValue = true;
        tail = tail->prev;
        delete tail->next;
        numberOfNodes--;
        setTailNext(numberOfNodes);
    }

    return removedValue;
}
//EOF

template<typename E>
bool DoublyLinkedList<E>::remove_first_target_instance(const E& value)
{
    //essentially the same algoirthim as remove_all_targets
    //except, will stop once ONE value has been removed

    Node<E> **current;   //PROC - track the current node indirectly
    Node<E> *removeNode; //PROC - temp while rewiring linked list
    bool removedValue;   //PROC - return value, true if a value is removed

    removedValue = false;
    current = &head;
    while (*current != tail && !removedValue) //only difference is !removedValue
    {
        if ((*current)->data == value)
        {
            //at most most removeNode = tail->prev
            removedValue = true;
            removeNode = *current;
            (*current)->next->prev = (*current)->prev;
            *current = (*current)->next;
            delete removeNode;

            numberOfNodes--;
        }
        else
            current = &((*current)->next);
    }

    if (tail == head)
    {
        if (numberOfNodes != 0 && tail->data == value)
        {   //single node with specified value
            removedValue = true;
            delete tail;
            head = tail = nullptr;
            numberOfNodes--;
        }
    }
    else if (tail->data == value) //linked list at least has two nodes.
    {
        removedValue = true;
        tail = tail->prev;
        delete tail->next;
        numberOfNodes--;
        setTailNext(numberOfNodes);
    }

    return removedValue;
}

/****************************************************************
 * 
 *  Method operator=: Class DoublyLinkedList
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Overload of the "=" operator. Do a deep copy of the passed
 *  in object. 
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Both the calling list and the passed in list can be
 *      empty, with no nodes, or any amount of nodes.
 *  POST-CONDITIONS
 *      The length of the calling object's linked list is
 *      assured to be changed if the passed in "that" linked
 *      list a different size. The only time the size will
 *      not change is the two linked list are of the exact same
 *      length. The calling object's memory associated with
 *      the linked list is automatically cleaned up or expanded
 *      according to the the size of "that".
****************************************************************/
template<typename E>
DoublyLinkedList<E>& DoublyLinkedList<E>::operator=(const DoublyLinkedList<E>& that)
{
    Node<E> *current_that;  //PROC - track node from "that"
    Node<E> *current;       //PROC - track node from calling obj.
    Node<E> *newTail;       //PROC - in the event calling obj.'s list is bigger

    this->numberOfNodes = that.numberOfNodes; //will always happen no matter what

    //avoid case were same object is on both
    //sides of the "=" operator.
    if (this == &that)
        return *this;       //just return the calling object
    
    //passed in list is empty
    if (that.head == nullptr)
    {
        clear();
        return *this;
    }

    //current object has no nodes or one node
    //and "that" also at least has one node
    if (head == tail)
    {
        current_that = that.head;
        if (head == nullptr) //empty list
        {
            head = tail = new Node<E>(current_that->data);
            setHeadPrev(numberOfNodes);
            setTailNext(numberOfNodes);
        }
        else
            head->data = current_that->data;
        
        current_that = current_that->next;
        while (current_that != getTrueEndNode())
        {
            tail->next = new Node<E>(current_that->data);
            tail->next->prev = tail;
            tail = tail->next;
            current_that = current_that->next;
        }
        return *this;
    }

    //Current condtions include:
    //NOT self referential, that is a DoublyLinkedList with at least one node
    //and the current object (*this) has least has two nodes.
    current = head;
    current_that = that.head;
    while (current != getTrueEndNode() && current_that != that.getTrueEndNode())
    {
        current->data = current_that->data;
        current = current->next;
        current_that = current_that->next;
    }

    //calling object's list is smaller, need to expand
    if (this->numberOfNodes < that.numberOfNodes)
    {
        while (current_that != nullptr)
        {
            tail->next = new Node<E>(current_that->data);
            tail->next->prev = tail;
            tail = tail->next;
            current_that = current_that->next;
        }
    }
    //need to cut off some fat
    else if (this->numberOfNodes > that.numberOfNodes)
    {
        //since we are assured by now the calling object has at
        //least two nodes, and the passed in linked list "that"
        //has at least one node, 
        //current at most is pointing to the same memory as tail.
        //current->prev would therefore be head at most.
        newTail = current->prev;
        while (current != tail)
        {
            current = current->next;
            delete current->prev;
        }
        delete tail;
        tail = newTail;
        tail->next = nullptr;
    }
    //else both list were of the exact same size.

    return *this;
}
//EOF

template<typename E>
void DoublyLinkedList<E>::clear(void)
{
    while (head != tail)
    {
        head = head->next;
        delete head->prev;
    }

    delete tail;
    head = tail = nullptr;
    numberOfNodes = 0;

    updateEndNode_Interface_Node();
    updateBeginNode_Interface_Node();
}
//EOF

template<typename E>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<E>& doubly_linsked_list)
{
    doubly_linsked_list.display(out);
    return out;
}

#endif //DOUBLY_LINKED_LIST_CLASS_CPP