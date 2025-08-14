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
int nearestLowerPowerOf2(int size);

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

// ---------------------------------------------------- Orthodox Canonical Form -------------------------------------------------------------------------------------
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

// ---------------------------------------------------- Member Template Functions -------------------------------------------------------------------------------------

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

template <typename Container>
void printContainer(const Container &c)
{
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename Container>
std::ostream& printContainer(std::ostream& os, Container &c)
{
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        os << *it << " ";
    return os;
}

template <typename Container>
std::ostream& operator <<(std::ostream& os, const PmergeMe<Container>& origin)
{
    return printContainer(os, origin.getContainer());
};

// ---------------------------------------------------- Helper Template Functions -------------------------------------------------------------------------------------

template <typename Container>
Container populateContainer(int size, char **arguments)
{
    unsigned int    num;
    Container       c;

    for (int i = 1; i < size; ++i)
    {
        if (!safeStrToUnsignedInt(arguments[i], num)) throw std::runtime_error("Invalid argument.");
        c.push_back(num);
    }
    return c;
};

// index is always index of the last element in the box, as in the Ford-Johnson algorithm, this element is used for comparison
template <typename Container>
void compareAndSwapBoxes(int boxSize, Container& container)
{
    typename Container::iterator it1 = container.begin() + boxSize - 1;
    typename Container::iterator it2 = it1 + boxSize;

    while(std::distance(it2, container.end()) >= static_cast<int>(container.size() % (boxSize * 2))) // odd numbers/containers won't be swapped
    {   
        if (*it1 > *it2) std::swap_ranges(it1 - boxSize + 1, it1 + 1, it2 - boxSize + 1);
        it1 += 2 * boxSize;
        it2 += 2 * boxSize;
    }
};

// ---------------------------------------------------- Template Specialization Functions -------------------------------------------------------------------------------------

// template<> means is explicit template specialization
//  empty angle brackets <> mean it is no longer a template definition for a generic T, but that the type parameters are already fixed, in this case to either vector or deque, and that it will be the one exact, concrete version of that function
template <>
inline void PmergeMe<std::vector<unsigned int> >::sort()
{
    // 1. split by powers of 2 (always 2 pairs but n higher levels): 1 1 1 1 1 1 1 1 1 1 1 --> (1 1) (1 1) (1 1) (1 1) (1 1) (1) --> ((1 1) (1 1)) ((1 1) (1 1)) [(1 1) (1)] --> [((1 1) (1 1)) ((1 1) (1 1))] [(1 1) (1)]
    int maxBoxSize = nearestLowerPowerOf2(_container.size());
    int boxSize = 1;
    while (boxSize <= maxBoxSize)
    {
        compareAndSwapBoxes(boxSize, _container);
        boxSize *= 2;
    }
};

template <>
inline void PmergeMe<std::deque<unsigned int> >::sort()
{
    int maxBoxSize = nearestLowerPowerOf2(_container.size());
    int boxSize = 1;
    while (boxSize <= maxBoxSize)
    {
        compareAndSwapBoxes(boxSize, _container);
        boxSize *= 2;
    }
};