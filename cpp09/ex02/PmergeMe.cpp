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
    std::vector<std::pair<int, int> > pairContainer = _initialPairing(_container, leftover); // overrides leftover, if any
    _container.clear(); // removes all elements
    printPairsContainer(pairContainer, 0);
    _mergeInsertion(_container, pairContainer, leftover);
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

std::vector<std::pair<int, int> > PmergeMe::_initialPairing(std::vector<int>& container, int& leftover)
{
    std::vector<std::pair<int, int> > pairedContainer;
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

// Creates new MAIN - creates pairs from largest elements of pairs, sorts in-pair, and puts to container of pairs
void PmergeMe::_createMain(std::vector<std::pair<int,int> >& pairContainer, std::vector<std::pair<int,int> >& main, std::vector<std::pair<int,int> >::iterator& it1)
{
    for (it1 = pairContainer.begin(); it1 != pairContainer.end() && it1 + 1 !=  pairContainer.end(); ++it1)
    {
        // if elements in the pair are not in order, swap their values
        if ((*it1).second > (*(it1 + 1)).second)
            std::iter_swap(it1, it1 + 1);
        main.push_back(std::make_pair((*it1).second, (*(it1 + 1)).second));
        it1 += 1; // protect against odd input - leftover
    }
    // if there is leftover, it is ignored when adding to main and in caller it is passed to recursion - to main, only valid pairs get in
};

// maybe this is not optimal since it first must find the upperBound by making comparisons ? 
void PmergeMe::_binaryInsertion(std::vector<int>& sortedContainer, int value, int upperBound)
{
    std::cout << "Binary insert: " << value << " with upper bound " << upperBound << std::endl;
    std::vector<int>::iterator limit = sortedContainer.begin(); // place end iterator before upper bound
    while (limit != sortedContainer.end() && *limit < upperBound)
        ++limit;

    std::vector<int>::iterator low = sortedContainer.begin();
    std::vector<int>::iterator high = limit;
    // binary search
    while (low < high)
    {
        std::vector<int>::iterator mid = low + (high - low) / 2; // for even numbers it selects the left(first,sooner) one as middle
        if (*mid < value)
            low = mid + 1;
        else
            high = mid;
    }
    sortedContainer.insert(low, value);
};

// TODO !!!
// we take toInsert that was just inserted and move it to the next viable one based on Jacobsthal numbers 
// index keeps which element was last inserted
// when index == prevJacobsthal, increase index, move toInsert up
// when index  > prevJacobsthal 
void getNextJacobsthalEl(std::vector<std::pair<int, int> >::iterator& toInsert, std::vector<std::pair<int, int> >& pairContainer, int& prevJacobsthal, int& index)
{
    // not using jacobsthal but going from beginning
    (void)pairContainer;
    (void)index;
    (void)prevJacobsthal;
    ++toInsert;

   
};

void PmergeMe::_mergeInsertion(std::vector<int>& sortedContainer, std::vector<std::pair<int, int> >& pairContainer, int& leftover)
{
    // debug
    std::cout << "MAIN: ";
    printPairsContainer(pairContainer, 1);
    if (leftover > 0) std::cout << " ( leftover " << leftover << ")" << std::endl;
    else std::cout << " ( leftover none )" << std::endl;

    // BASE CASE - must be before recustion call so we can actually escape
    if (pairContainer.size() <= 1)
    {
        sortedContainer.push_back((*pairContainer.begin()).second); // populate sorted container with the larger element, smaller will be added outside the recursion step
        sortedContainer.insert(sortedContainer.begin(), (*pairContainer.begin()).first); // insert to front - always smaller
        if (leftover > -1)
            _binaryInsertion(sortedContainer, leftover, (leftover > *(--sortedContainer.end())) ? leftover : *(--sortedContainer.end()));
        return ;
    }

    // create main from larger elements for next recursion step
    std::vector<std::pair<int, int> >::iterator it1;
    std::vector<std::pair<int, int> > main;
    _createMain(pairContainer, main, it1);
    int newLeftover = (it1 != pairContainer.end()) ? (*it1).second : -1; // store leftover, if any, so we can insert it

    // recurse on main
    _mergeInsertion(sortedContainer, main, newLeftover); // the elements from main are already in in sorted sequence, pass in leftover without storing it 
    
    std::cout << "Sorted container: " << sortedContainer << "." << std::endl;

    // TODO: function that finds me the next element to sort form the main, starting at next jacobsthal, then reducing until hits previous jacobsthal, since that one is already sorted into final container
    // // without comparing, we can store first mains's small before its large, which is at the beginning
    int Jacobsthal = 1;
    int index = 1;
    // sortedContainer.insert(sortedContainer.begin(), (*(main.begin())).first);
    std::vector<std::pair<int, int> >::iterator toInsert = pairContainer.begin(); // without comparing, we can store first mains's small before its large, which is at the beginning
    while (toInsert != pairContainer.end())
    {
        // we are not adding elements from pairContainer(main) since they are already in from the previous recusrions step - we are only checking them but adding their smaller pairings
        _binaryInsertion(sortedContainer, (*toInsert).first, (*toInsert).second);
        getNextJacobsthalEl(toInsert, pairContainer, Jacobsthal, index); // updates Jacobsthal when necessary
        std::cout << "end" << std::endl;
    }

    if (leftover > -1)
        _binaryInsertion(sortedContainer, leftover, (leftover > *(--sortedContainer.end())) ? leftover : *(--sortedContainer.end())); // when inserting leftovers, if it is larger than teh max element, it would never get to back becasue last el is largest and set as upper bound - set this leftover el as upperbound instead
};