#include "PmergeMe.hpp"

#include <string>
#include <iostream>
#include <exception>
#include <cerrno>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream> // string streams

// ---------------------------------------------------- Orthodox Canonical Form -------------------------------------------------------------------------------------
PmergeMe::PmergeMe()
{
    throw std::runtime_error("Cannot instantiate with empty default constuctor. Aborting.");
};

PmergeMe::PmergeMe(const std::vector<int>  & container) : _container(container) {};

PmergeMe::PmergeMe(const PmergeMe& origin) : _container(origin._container) {};

PmergeMe& PmergeMe::operator =(const PmergeMe& origin)
{
    if (this != &origin)
        std::cerr << "Cannot copy assign on class with const members. Returning without change." << std::endl;
    return *this;
};

PmergeMe::~PmergeMe() {};

std::ostream& operator <<(std::ostream& os, const PmergeMe& origin)
{
    const std::vector<int>& c = origin.getContainer();
    for (std::vector<int>::const_iterator it = c.begin(); it != c.end(); ++it)
        os << *it << " ";
    return os;
};

const std::vector<int>  & PmergeMe::getContainer() const 
{
    return _container;
};

// ---------------------------------------------------- Algorithm -------------------------------------------------------------------------------------

void PmergeMe::sort()
{
    if (_container.size() <= 3) return _sortThree();

    int leftover = -1;
    std::vector<Pair> pairContainer = _initialPairing(_container, leftover); // overrides leftover, if any
    _container.clear(); // removes all elements
    printPairsContainer(pairContainer, 0);
    std::vector<std::vector<Pair>::iterator> main;
    main.reserve(pairContainer.size());
    for (std::vector<Pair>::iterator it = pairContainer.begin(); it != pairContainer.end(); ++it)
        main.push_back(it);  
    _mergeInsertion(main, leftover);
}; 

void    PmergeMe::_sortThree()
{
    std::vector<int>::iterator it = _container.begin();
    if (_container.size() <= 1)
        return ;
    if (_container.size() == 2)
    {
        if (*it > *(it + 1)) std::iter_swap(it, it + 1);
        return ;
    }
    if (*(it + 1) > *(it + 2)) std::iter_swap(it + 1, it + 2);
    if (*(it) > *(it + 2)) std::iter_swap(it, it + 2);
    if (*it > *(it + 1)) std::iter_swap(it, it + 1);
};

std::vector<Pair> PmergeMe::_initialPairing(std::vector<int>& container, int& leftover)
{
    std::vector<Pair> pairedContainer;
    
    pairedContainer.reserve((container.size() + 1) / 2);
    std::vector<int>::iterator it;
    for (it = container.begin(); it != container.end() && it + 1 !=  container.end(); ++it)
    {
        if (*it > *(it + 1))
            std::iter_swap(it, it + 1); // swap pairs if needed
        pairedContainer.push_back(std::make_pair(*it, *(it + 1)));
        it += 1;
    }
    if (it != container.end())
        leftover = *it;
    return pairedContainer;
};

// 1. the pairContainer has pairs
// 2. first main stores iterators to these pairs in pairContainer
// 3. create new main from larger elements -> this new main stores iterators of teh larger elements and put it to recursion as input variable
// 4. again create new main from larger elements and put it to recursion
// 5. the base case is hit - put the element into resulting vector of pointers 
// 6. go to the previous level - iterate the input container (for now from start) and call binary search on the dereferenced iterator's smaller element to put it to resultnig container, using the iterator as bounding element, and put entire iterator here


// maybe this is not optimal since it first must find the upperBound by making comparisons ? 
void PmergeMe::_binaryInsertion(std::vector<Pair>& to, std::vector<Pair>::iterator& toInsert, std::vector<Pair>::iterator& upperBound)
{
    std::vector<Pair>::iterator low = to.begin();
    std::vector<Pair>::iterator high = upperBound;
    int value = (*toInsert).first;
    std::cout << "Binary insert: " << value << " with upper bound at " << (*high).second << std::endl;
    // binary search
    while ((*low).second < (*high).second)
    {
        std::vector<Pair>::iterator mid = low + (high - low) / 2; // for even numbers it selects the left(first,sooner) one as middle
        if ((*mid).second < value)
            low = mid + 1;
        else
            high = mid;
    }
    sortedContainer.insert(low, toInsert);
};

// TODO !!!
void getNextJacobsthalEl(std::vector<Pair>::iterator& toInsert, std::vector<Pair>& pairContainer, int& prevJacobsthal, int& index)
{
    // not using jacobsthal but going from beginning
    (void)pairContainer;
    (void)index;
    (void)prevJacobsthal;
    ++toInsert;

   
};

// takes in vector of iterators
void PmergeMe::_mergeInsertion(std::vector<Pair*>& input, int& leftover)
{
    // debug
    std::cout << "INPUT: ";
    printPairsContainer(input, 1);
    if (leftover > 0) std::cout << " ( leftover " << leftover << ")" << std::endl;
    else std::cout << " ( leftover none )" << std::endl;

    // BASE CASE - must be before recustion call so we can actually escape
    if (input.size() <= 1)
    {
        return ;
    }

    // create main from larger elements for next recursion step
    std::vector<Pair*>::iterator it1;
    std::vector<Pair*> main;
    for (it1 = input.begin(); it1 != input.end() && it1 + 1 !=  input.end(); ++it1)
    {
        // if elements in the pair are not in order, swap their values
        if ((*it1).second > (*(it1 + 1)).second)
            std::iter_swap(it1, it1 + 1);
        main.push_back(std::make_pair((*it1).second, (*(it1 + 1)).second));
        it1 += 1; // protect against odd input - leftover
    }
    int newLeftover = (it1 != pairContainer.end()) ? (*it1).second : -1; // store leftover, if any, so we can insert it

    // recurse on main
    _mergeInsertion(sortedContainer, main, newLeftover); // the elements from main are already in in sorted sequence, pass in leftover without storing it 

    std::vector<Pair*>::iterator it2 = input.begin();
    while (it2 != input.end())
    {
            _binaryInsert(main, *(it2), it2);
            it2++;
    }

    if (leftover > -1)
        _binaryInsertion(main, std::make_pair(-1, leftover), main.end()); // when inserting leftovers, if it is larger than teh max element, it would never get to back becasue last el is largest and set as upper bound - set this leftover el as upperbound instead
};