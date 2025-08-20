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
int calculateMaxNumberOfComparisons(int n);

template <typename Container>
class PmergeMe
{
    private:
        Container _container;
        int       _comparisonCount;
        void      comparePairs(int level, typename Container::iterator& containerBegin, typename Container::iterator& containerEnd);
        void      mergeJacobsthalBinaryInsert(int boxSize);

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
        if (arguments[i] == NULL || arguments[i][0] == '\0') throw std::runtime_error("Invalid argument.");
        if (!safeStrToUnsignedInt(arguments[i], num)) throw std::runtime_error("Invalid argument.");
        if (std::find(c.begin(), c.end(), num) != c.end()) throw std::runtime_error("Duplicate arguments.");
        c.push_back(num);
    }
    return c;
};
// levelN = size of container is 2^N
// level0 = single numbers - 1 - access every one element with itself -> prevent
// level1 = pairs of elements - 2 - compare every second eeement with the next
// level2 = pairs of pairs - 4 - compare every 4th element with next 4th element
// level3 = ...
// index is always index of the last element in the box, as in the Ford-Johnson algorithm, this element is used for comparison
template <typename Container>
void PmergeMe<Container>::comparePairs(int level, typename Container::iterator& containerBegin, typename Container::iterator& containerEnd)
{
    typedef Container::iterator& first = _container.begin();
    typedef Container::iterator& second = first + pow(2, level);
    while (std::distance)
    {
        comparePairs(level / 2, containerBegin, containerBegin + pow(2, level))
        comparePairs(level / 2, containerBegin + pow(2, level) + 1, containerBegin + 2 * pow(2, level))
    }
    if (containerEnd)


};

// ---------------------------------------------------- Template Specialization Functions -------------------------------------------------------------------------------------

// template<> means is explicit template specialization
//  empty angle brackets <> mean it is no longer a template definition for a generic T, but that the type parameters are already fixed, in this case to either vector or deque, and that it will be the one exact, concrete version of that function
template <>
inline void PmergeMe<std::vector<unsigned int> >::sort()
{
    int maxLevel = nearestLowerPowerOf2(_container.size() / 2);
    // comparePairs(maxLevel, _container.begin(), --_container.end());
    // 1. create pairs of 2 elements
    // 2. sort this pair
    // 3. recursion
    // 4. take the smaller element of pair and put it 
    
    
};

template <>
inline void PmergeMe<std::deque<unsigned int> >::sort()
{
   
};