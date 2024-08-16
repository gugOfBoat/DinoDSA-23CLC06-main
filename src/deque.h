#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>

template <typename T>
class Deque {
public:
    // Constructor with default capacity
    Deque(int capacity = 100);
    
    // Destructor
    ~Deque();
    
    // Push element to the back of the deque
    void push_back(const T& item);
    
    // Push element to the front of the deque
    void push_front(const T& item);
    
    // Pop element from the back of the deque
    void pop_back();
    
    // Pop element from the front of the deque
    void pop_front();
    
    // Get the front element
    T& front();
    
    // Get the back element
    T& back();
    
    // Check if the deque is empty
    bool isEmpty() const;
    
    // Clear the deque
    void clear();
    
    // Get the current size of the deque
    int size() const;
    
    // Overloaded operator []
    T& operator[](int index);
    const T& operator[](int index) const;

private:
    T* data;           // Array to store the deque elements
    int frontIdx;      // Index of the front element
    int backIdx;       // Index of the next available position at the back
    int numElements;   // Current number of elements in the deque
    int capacity;      // Capacity of the deque
};

// Definitions of the template functions
template <typename T>
Deque<T>::Deque(int cap)
    : capacity(cap), numElements(0), frontIdx(0), backIdx(0) {
    data = new T[capacity];
}

template <typename T>
Deque<T>::~Deque() {
    delete[] data;
}

template <typename T>
void Deque<T>::push_back(const T& element) {
    if (numElements == capacity) {
        throw std::overflow_error("Deque is full");
    }
    data[backIdx] = element;
    backIdx = (backIdx + 1) % capacity;
    numElements++;
}

template <typename T>
void Deque<T>::push_front(const T& element) {
    if (numElements == capacity) {
        throw std::overflow_error("Deque is full");
    }
    frontIdx = (frontIdx - 1 + capacity) % capacity;
    data[frontIdx] = element;
    numElements++;
}

template <typename T>
void Deque<T>::pop_back() {
    if (numElements > 0) {
        backIdx = (backIdx - 1 + capacity) % capacity;
        numElements--;
    } else {
        throw std::underflow_error("Deque is empty");
    }
}

template <typename T>
void Deque<T>::pop_front() {
    if (numElements > 0) {
        frontIdx = (frontIdx + 1) % capacity;
        numElements--;
    } else {
        throw std::underflow_error("Deque is empty");
    }
}

template <typename T>
T& Deque<T>::front() {
    if (isEmpty()) {
        throw std::underflow_error("Deque is empty");
    }
    return data[frontIdx];
}

template <typename T>
T& Deque<T>::back() {
    if (isEmpty()) {
        throw std::underflow_error("Deque is empty");
    }
    return data[(backIdx - 1 + capacity) % capacity];
}

template <typename T>
bool Deque<T>::isEmpty() const {
    return numElements == 0;
}

template <typename T>
void Deque<T>::clear() {
    frontIdx = 0;
    backIdx = 0;
    numElements = 0;
}

template <typename T>
int Deque<T>::size() const {
    return numElements;
}

template <typename T>
T& Deque<T>::operator[](int index) {
    return data[(frontIdx + index) % capacity];
}

template <typename T>
const T& Deque<T>::operator[](int index) const {
    return data[(frontIdx + index) % capacity];
}

#endif // DEQUE_H
