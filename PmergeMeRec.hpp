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
#include <utility>

bool safeStrToPositiveInt(const char* str, int &res);
int nearestLowerPowerOf2(int size);
int calculateMaxNumberOfComparisons(int n);

// Primary template declaration (needed for specializations)
template <typename Container>
inline void _initialPairing(Container _container);

template <typename Container>
class PmergeMe
{
    private:
        Container           _container;
        int                 _comparisonCount;

        std::vector<int>                    _mergeInsertion(std::vector<std::pair<int, int> >& pairContainer);
        std::vector<std::pair<int, int> >   _initialPairing(Container& _container);

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
    int    num;
    Container       c;

    for (int i = 1; i < size; ++i)
    {
        if (arguments[i] == NULL || arguments[i][0] == '\0') throw std::runtime_error("Invalid argument.");
        if (!safeStrToPositiveInt(arguments[i], num)) throw std::runtime_error("Invalid argument.");
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
std::vector<int> PmergeMe<Container>::_mergeInsertion(std::vector<std::pair<int, int> >& pairContainer)
{



};

// ---------------------------------------------------- Template Specialization Functions -------------------------------------------------------------------------------------

template <>
inline std::vector<std::pair<int, int> > _initialPairing(std::vector<int> _container)
{

};

template <>
inline std::deque<std::pair<int, int> > _initialPairing(std::deque<int> _container)
{

};

// template<> means is explicit template specializatio
//  empty angle brackets <> mean it is no longer a template definition for a generic T, but that the type parameters are already fixed, in this case to either vector or deque, and that it will be the one exact, concrete version of that function
template <typename Container>
inline void PmergeMe<Container>::sort()
{
    std::vector<std::pair<int, int> > pairContainer = _initialPairing(_container);
    std::vector<int> sorted = _mergeInsertion(pairContainer);
    
    
};