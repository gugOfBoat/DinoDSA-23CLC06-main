#ifndef DEQUE_H
#define DEQUE_H

template <class DataType>
class DequeNode;
template <class DataType>
class Deque;

template <class DataType>
class DequeNode
{
    friend class Deque<DataType>;
private:
    DataType data;
    DequeNode *next;
public:
    DequeNode(DataType in_data, DequeNode *in_next = nullptr);
};

template <class DataType>
class Deque
{
private:
    DequeNode<DataType> *head;
    DequeNode<DataType> *tail;
    int size;
public:
    Deque();
    ~Deque();
    bool isEmpty();
    void push_back(DataType data);
    void push_front(DataType data);
    void pop_back();
    void pop_front();
    DataType front();
    DataType back();
    void clear();
};

#endif