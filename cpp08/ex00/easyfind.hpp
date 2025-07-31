#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>

template <typename T>
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::out_of_range("Value not found in container");
    return it;
}

// overload for const containers - will use const_iterator
template<typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::out_of_range("Value not found");
    return it;
}

#endif