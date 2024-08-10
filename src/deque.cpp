#include "deque.h"

template <class DataType>
DequeNode<DataType>::DequeNode(DataType in_data, DequeNode *in_next)
{
    data = in_data;
    next = in_next;
}

template <class DataType>
Deque<DataType>::Deque()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class DataType>
Deque<DataType>::~Deque()
{
    clear();
}

template <class DataType>
void Deque<DataType>::clear()
{
    while (head != nullptr)
    {
        auto next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
}

template <class DataType>
bool Deque<DataType>::isEmpty()
{
    return (size == 0);
}

template <class DataType>
void Deque<DataType>::push_back(DataType data)
{
    DequeNode<DataType> * newNode = new DequeNode<DataType>(data);
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}
template <class DataType>
void Deque<DataType>::push_front(DataType data)
{
    auto newNode = new DequeNode<DataType>(data);
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

template <class DataType>
void Deque<DataType>::pop_front()
{
    if (head == nullptr)
        return;
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        auto newHead = head->next;
        delete head;
        head = newHead;
    }
    --size;
}
template <class DataType>
void Deque<DataType>::pop_back()
{
    if (head == nullptr)
        return;
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        auto newTail = head;
        while (newTail->next != tail)
            newTail = newTail->next;
        delete tail;
        tail = newTail;
    }
    --size;
}

template <class DataType>
DataType Deque<DataType>::front()
{
    return head->data;
}

template <class DataType>
DataType Deque<DataType>::back()
{
    return tail->data;
}