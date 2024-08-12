#include "vector.h"

template <class DataType>
Vector<DataType>::Vector()
{
    maxsize = DEFAULT_MAXSIZE;
    used = 0;
    array = new DataType[maxsize];
}
template <class DataType>
Vector<DataType>::Vector(int init_size)
{
    maxsize = init_size + DEFAULT_MAXSIZE / 2;
    used = init_size;
    array = new DataType[maxsize];
}
template <class DataType>
Vector<DataType>::Vector(int init_size, DataType init_value)
{
    maxsize = init_size + DEFAULT_MAXSIZE / 2;
    size = init_size;
    array = new DataType[maxsize];
    for (int i = 0; i < size; i++)
        array[i] = init_value;
}
template <class DataType>
Vector<DataType>::~Vector()
{
    delete [] maxsize;
}

template <class DataType>
void Vector<DataType>::push_back(DataType data)
{
    if (used >= maxsize)
        reallocate(maxsize + 1);
    array[used++] = data;
}
template <class DataType>
void Vector<DataType>::pop_back()
{
    --used;
}
template <class DataType>
void Vector<DataType>::clear()
{
    used = 0;
}
template <class DataType>
void Vector<DataType>::swap(Vector &vtr2)
{
    swap(vtr2.maxsize, maxsize);
    swap(vtr2.used, used);
    
    auto tmp = array;
    array = vtr2.array;
    vtr2.array = tmp;
}

template <class DataType>
DataType& Vector<DataType>::front()
{
    if (used <= 0)
        throw "Cannot get front of an empty vector";
    return array[0];
}
template <class DataType>
DataType& Vector<DataType>::back()
{
    if (used <= 0)
        throw "Cannot get back of an empty vector";
    return array[used-1];
}
template <class DataType>
DataType& Vector<DataType>::operator[](int idx)
{
    if (used <= 0)
        throw "Cannot get element of an empty vector";
    if (idx < 0 || idx >= used)
        throw "Index invalid";
    return array[idx];
}

template <class DataType>
int Vector<DataType>::size()
{
    return used;
}
template <class DataType>
int Vector<DataType>::capacity()
{
    return maxsize;
}

template <class DataType>
void Vector<DataType>::reallocate(int newsize)
{
    if (newsize <= maxsize)
        return;
    auto tmp = new DataType[newsize];
    for (int i = 0; i < used; i++)
        tmp[i] = array[i];
    delete [] array;
    array = tmp;
}