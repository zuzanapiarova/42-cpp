#include "Array.hpp"

#include <stdexcept>

template <typename T>
Array<T>::Array () : _size(0), _array(NULL)
{
    std::cout << "Array default constructor called." << std::endl;
};

template <typename T>
Array<T>::Array(unsigned int n) : _size(n)
{
    std::cout << "Array overload constructor called." << std::endl;
    _array = new T[n](); // value-initialized thanks to ()
}

template <typename T>
Array<T>::Array(const Array<T>& origin)
{
    std::cout << "Array copy constructor called." << std::endl;
    *this = origin;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& origin)
{
    std::cout << "Array copy assignment opertor called." << std::endl;
    if (this != &origin)
    {
        delete[] _array;
        _size = origin._size;
        if (_size > 0)
        {
            _array = new T[_size]; // not value-initilized - we copy values right away from other object
            for (unsigned int i = 0; i < _size; ++i)
                _array[i] = origin._array[i];
        }
        else
            _array = NULL;
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
    if (index >= _size)
        throw std::out_of_range("Index out of bounds");
    return _array[index];
};

// overload this operator because for const Array<T>, a[0] = 10 must be forbidden - if not const, it returns a reference, that the user could try to assign
template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
    if (index >= _size)
        throw std::out_of_range("Index out of bounds");
    return _array[index];
}

template <typename T>
Array<T>::~Array()
{
    std::cout << "Array destructor called." << std::endl;
    delete[] _array;
};

template <typename T>
unsigned int    Array<T>::size() const
{
    return _size;
}