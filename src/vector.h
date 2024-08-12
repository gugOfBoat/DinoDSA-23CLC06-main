#ifndef VECTOR_H
#define VECTOR_H

// void swap(int a, int b)
// {
//     auto tmp = a;
//     a = b;
//     b = tmp;
// }

template <class DataType>
class Vector
{
private:
    const int DEFAULT_MAXSIZE = 100;
    int maxsize;
    int used;
    DataType *array;

    void reallocate(int newsize);
public:
    Vector();
    Vector(int init_size);
    Vector(int init_size, DataType init_value);
    ~Vector();

    void push_back(DataType data);
    void pop_back();
    void clear();
    void swap(Vector &vtr2);

    DataType &front();
    DataType &back();
    DataType &operator[](int idx);

    int size();
    int capacity();
};

#endif