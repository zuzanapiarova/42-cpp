#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>
#include <string>

template <typename T>
class Array
{
    private:
        unsigned int  _size;
        T*            _array;

    public:
        Array();
        Array(unsigned int n);
        Array(const Array& origin);
        Array& operator =(const Array& origin);
        T& operator [](unsigned int index);
        const T& operator [](unsigned int index) const ;
        ~Array();

        unsigned int size() const ;

};

#include "Array.tpp"

#endif