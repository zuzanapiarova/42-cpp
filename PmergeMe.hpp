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
        void      compareAndSwapBoxes(int boxSize, Container& container);
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

// index is always index of the last element in the box, as in the Ford-Johnson algorithm, this element is used for comparison
template <typename Container>
void PmergeMe<Container>::compareAndSwapBoxes(int boxSize, Container& container)
{
    typename Container::iterator it1 = container.begin() + boxSize - 1;
    typename Container::iterator it2 = it1 + boxSize;

    while(std::distance(it2, container.end()) >= static_cast<int>(container.size() % (boxSize * 2))) // odd numbers/containers won't be swapped
    {   
        if (*it1 > *it2)
        {
            std::swap_ranges(it1 - boxSize + 1, it1 + 1, it2 - boxSize + 1);
            _comparisonCount++;
        }     
        it1 += 2 * boxSize;
        it2 += 2 * boxSize;
    }
};

template <typename Container>
void PmergeMe<Container>::mergeJacobsthalBinaryInsert(int boxSize)
{
    // every boxSize size section, starting at every boxSize-th element, compare:
    // first(b1), second(a1) - not considered
    // from third(b2), every other element(bs), skipping every second element(as)

    int Jacobsthal = 3;
    // this iterator is moving on each b element, starting with b2
    // typename Container::iterator main = _container.begin() + boxSize - 1; // b1, a1, a2, a3, ..., an -> move by boxSize * 2
    // typename Container::iterator pend = _container.begin() + (boxSize * 3) - 1; // b2, b3, ..., bn -> move by boxSize * 2
    typename Container::iterator b = _container.begin() + (boxSize * Jacobsthal * 2 - boxSize) - 1; // b element - des not exist for 2 highest levels
    typename Container::iterator bound = b; // bounding element - do not have to go to it and behinf, since all of it is bigger
    while (std::distance(b, _container.end()) >= boxSize)
    {
        typename Container::iterator binaryInsertIter = _container.begin();
        while (binaryInsertIter != a)
        int newPos = binaryInsertion(b, a); // returns number of boxes it was placed - based on probably also new b and new a changed and we will calculate it in the new a and b
        // all following code gets the next Jacobsthal box on turn (smaller, or if need larger, get the nearest box that is in the sequence)
        Jacobsthal--;
        if (Jacobsthal < 2)
            Jacobsthal = getNextJacobsthal(Jacobsthal);
        b = _container.begin() + (boxSize * Jacobsthal * 2 - boxSize) - 1;
        while (std::distance(b, _container.end()) < 0)
        {
            Jacobsthal--;
            b = _container.begin() + (boxSize * Jacobsthal * 2 - boxSize) - 1;
        }
        bound = b;
    }
    // we get Jacobsthal number from 3 and check if it exists - we find nearest smaller Jacobsthal element 
    // and binary insert all bs from it downward, based on the last element in the box 
    // iterate container every other boxSize element, apart from the first one (starting from boxSize*3, then incrementing by boxSize*2)
    // cehck if we have jacobsthal number in upper iteration - if not, move to next Jacobsthal number
    // if yes, binary insert the found box to the corect place, and all smaller also binary insert, one by one
    // then continue to decrease box sizes, always reseting jacobsthal number to 3 and repeat
};


// ---------------------------------------------------- Template Specialization Functions -------------------------------------------------------------------------------------

// template<> means is explicit template specialization
//  empty angle brackets <> mean it is no longer a template definition for a generic T, but that the type parameters are already fixed, in this case to either vector or deque, and that it will be the one exact, concrete version of that function
template <>
inline void PmergeMe<std::vector<unsigned int> >::sort()
{
    // 1. splitting and sorting in-pair
    // --> split by powers of 2 and sort, recursively (always 2 pairs but n higher levels): 1 1 1 1 1 1 1 1 1 1 1 --> (1 1) (1 1) (1 1) (1 1) (1 1) (1) --> ((1 1) (1 1)) ((1 1) (1 1)) [(1 1) (1)] --> [((1 1) (1 1)) ((1 1) (1 1))] [(1 1) (1)]
    int maxBoxSize = nearestLowerPowerOf2(_container.size()); // size of the last-level single box, it is not in pair
    int boxSize = 1;
    while (boxSize <= maxBoxSize)
    {
        compareAndSwapBoxes(boxSize, _container);
        boxSize *= 2;
    }
    boxSize /= 2; // 16 get boxSize back to maxBoxSize
    // 2. insertion + merge
    std::cout << "Boxsize: " << boxSize << ", maxBoxSize: " << maxBoxSize << std::endl;
    while (boxSize >= 1)
    {
        mergeJacobsthalBinaryInsert(boxSize);
        boxSize /= 2;
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