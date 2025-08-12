# pragma once

#include <iostream>
#include <string>
#include <exception>
#include <istream>
#include <limits>
#include <cerrno>
#include <algorithm>
#include <vector>
#include <deque>

bool safeStrToUnsignedInt(const char* str, unsigned int &res);
std::vector<unsigned int> populateVector(int size, char **arguments);
std::deque<unsigned int> populateDeque(int size, char **arguments);


template <typename Container>
class PmergeMe
{
    private:
        Container _container;

    public:
        PmergeMe();
        PmergeMe(const Container& container);
        PmergeMe(const PmergeMe& origin);
        PmergeMe& operator =(const PmergeMe& origin);
        ~PmergeMe();
    
        void sort();
        Container& getContainer();
        const Container& getContainer() const ;

};

template <typename Container>
PmergeMe<Container>::PmergeMe()
{
    // std::cout << "PmergeMe default constructor called." << std::endl;
    throw std::runtime_error("Cannot instantiate with empty default constuctor. Aborting.");
};

template <typename Container>
PmergeMe<Container>::PmergeMe(const Container& container) : _container(container)
{
    // std::cout << "PmergeMe overload constructor called." << std::endl;
};

template <typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe& origin) : _container(origin._container)
{
    // std::cout << "PmergeMe copy constructor called." << std::endl;
};

template <typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator =(const PmergeMe& origin)
{
    // std::cout << "PmergeMe copy constructor called." << std::endl;
    if (this != &origin)
        _container = origin._container;
    return *this;
};

template <typename Container>
PmergeMe<Container>::~PmergeMe()
{
    // std::cout << "PmergeMe destructor called." << std::endl;
};
template <typename Container>
Container& PmergeMe<Container>::getContainer() 
{
    return _container;
};

template <typename Container>
const Container& PmergeMe<Container>::getContainer() const 
{
    return _container;
};

// template<> means is explicit template specialization
//  empty angle brackets <> mean it is no longer a template definition for a generic T, but that the type parameters are already fixed, in this case to either vector or deque, and that it will be the one exact, concrete version of that function
template <>
inline void PmergeMe<std::vector<unsigned int> >::sort()
{
    _container.push_back(1);
};

template <>
inline void PmergeMe<std::deque<unsigned int> >::sort()
{
    _container.push_back(2);
};

template <typename Container>
void printContainer(Container &c)
{
    for (typename Container::iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

