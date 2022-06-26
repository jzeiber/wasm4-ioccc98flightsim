#pragma once

#include <stddef.h>

template<class T>
class DynamicArray
{
public:

    typedef T *iterator;
    typedef size_t size_type;

    DynamicArray();
    DynamicArray(const size_type size, const T &val);
    DynamicArray(const DynamicArray<T> &rhs);
    ~DynamicArray();

    size_type size() const;
    size_type capacity() const;
    void reserve(const size_type capacity);

    void push_back(const T &val);
    void pop_back();
    bool empty() const;
    iterator begin();
    iterator end();
    T & front();
    T & back();

    void erase(const size_type pos);
    void clear();

    DynamicArray &operator=(const DynamicArray<T> &rhs);
    T &operator[](const size_type pos);
    T &operator[](const size_type pos) const;

private:
    T *m_array;
    size_type m_size;
    size_type m_capacity;
};

template<class T>
DynamicArray<T>::DynamicArray():m_array(nullptr),m_size(0),m_capacity(0)
{
    reserve(16);
}

template<class T>
DynamicArray<T>::DynamicArray(const size_type size, const T &val):m_array(nullptr),m_size(0),m_capacity(0)
{
    reserve(size);
    for(size_type i=0; i<size; i++)
    {
        m_array[i]=val;
    }
    m_size=size;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &rhs):m_array(nullptr),m_size(0),m_capacity(0)
{
    *this=rhs;
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
    delete [] m_array;
}

template<class T>
typename DynamicArray<T>::size_type DynamicArray<T>::size() const
{
    return m_size;
}

template<class T>
typename DynamicArray<T>::size_type DynamicArray<T>::capacity() const
{
    return m_capacity;
}

template<class T>
void DynamicArray<T>::reserve(const size_type capacity)
{
    if(capacity>0)
    {
        T *newarray=new T[capacity];
        for(size_type i=0; i<m_size && i<capacity; i++)
        {
            newarray[i]=m_array[i];
        }
        m_capacity=capacity;
        m_size=(m_size < m_capacity ? m_size : m_capacity);
        delete [] m_array;
        m_array=newarray;
    }
    else
    {
        delete [] m_array;
        m_array=nullptr;
        m_size=0;
        m_capacity=0;
    }
}

template<class T>
void DynamicArray<T>::push_back(const T &val)
{
    if(m_size==m_capacity)
    {
        reserve(m_capacity+16);
    }
    m_array[m_size++]=val;
}

template<class T>
void DynamicArray<T>::pop_back()
{
    if(m_size>0)
    {
        m_size--;
    }
}

template<class T>
typename DynamicArray<T>::iterator DynamicArray<T>::begin()
{
    return m_array;
}

template<class T>
typename DynamicArray<T>::iterator DynamicArray<T>::end()
{
    return m_array+size();
}

template<class T>
T &DynamicArray<T>::front()
{
    return m_array[0];
}

template<class T>
T &DynamicArray<T>::back()
{
    return m_array[m_size-1];
}

template<class T>
void DynamicArray<T>::erase(const size_type pos)
{
    if(pos>=0 && pos<m_size)
    {
        for(size_type i=pos; i<m_size-1; i++)
        {
            m_array[i]=m_array[i+1];
        }
        m_size--;
    }
}

template<class T>
void DynamicArray<T>::clear()
{
    m_size=0;
}

template<class T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &rhs)
{
    if(this!=*rhs)
    {
        delete [] m_array;
        m_array=nullptr;
        m_size=0;
        m_capacity=0;
        if(rhs.m_capacity>0)
        {
            reserve(rhs.m_capacity);
            for(size_type i=0; i<rhs.m_size; i++)
            {
                m_array[i]=rhs.m_array[i];
            }
        }
    }
    return *this;
}

template<class T>
T &DynamicArray<T>::operator[](const size_type pos)
{
    return m_array[pos];
}

template<class T>
T &DynamicArray<T>::operator[](const size_type pos) const
{
    return m_array[pos];
}
