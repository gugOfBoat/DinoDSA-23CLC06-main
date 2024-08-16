#include <iostream>
#include "deque.h"

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
    // Kiểm tra nếu đầy
    if (numElements == capacity) {
        // Xử lý tăng kích thước hoặc báo lỗi
    }
    data[backIdx] = element;
    backIdx = (backIdx + 1) % capacity;
    numElements++;
}

template <typename T>
void Deque<T>::push_front(const T& element) {
    // Kiểm tra nếu đầy
    if (numElements == capacity) {
        // Xử lý tăng kích thước hoặc báo lỗi
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
    }
}

template <typename T>
void Deque<T>::pop_front() {
    if (numElements > 0) {
        frontIdx = (frontIdx + 1) % capacity;
        numElements--;
    }
}

template <typename T>
T& Deque<T>::front() {
    return data[frontIdx];
}

template <typename T>
T& Deque<T>::back() {
    return data[backIdx - 1];
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

// Nạp chồng toán tử []
template <typename T>
T& Deque<T>::operator[](int index) {
    return data[(frontIdx + index) % capacity];
}

template <typename T>
const T& Deque<T>::operator[](int index) const {
    return data[(frontIdx + index) % capacity];
}

// Phương thức size
template <typename T>
int Deque<T>::size() const {
    return numElements;
}
