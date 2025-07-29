#ifndef ITER_HPP
# define ITER_HPP

#include <string>
#include <iostream>

// non-const elements
template <typename I>
void iter(I* arr, int len, void (*func)(I&))
{
    if (!arr)
        return ;

    for (int i = 0; i < len; i++)
        func(arr[i]);
}

// overloading for const elements
template <typename I>
void iter(const I* arr, int len, void (*func)(const I&))
{
    if (!arr)
        return;

    for (int i = 0; i < len; i++)
        func(arr[i]);
}

#endif
