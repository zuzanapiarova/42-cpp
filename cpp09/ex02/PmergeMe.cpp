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

// --------------------------------------- Orthodox Canonical Form ------------------------------------------------------

PmergeMe::PmergeMe()
{
    throw std::runtime_error("Cannot instantiate with empty default constuctor. Aborting.");
};

PmergeMe::PmergeMe(const std::vector<int>& vector, const std::deque<int>& deque) : _vector(vector), _deque(deque) {};

PmergeMe::PmergeMe(const PmergeMe& origin) : _vector(origin._vector), _deque(origin._deque) {};

PmergeMe& PmergeMe::operator=(const PmergeMe& origin)
{
    if (this != &origin)
        std::cerr << "Cannot copy assign on class with const members. Returning without change." << std::endl;
    return *this;
};
PmergeMe::~PmergeMe() {};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& container)
{
    for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); ++it)
    {
        os << *it << " ";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::deque<int>& container)
{
    for (std::deque<int>::const_iterator it = container.begin(); it != container.end(); ++it)
    {
        os << *it << " ";
    }

    return os;
}

void PmergeMe::_printPairsVector(const std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover)
{
	std::cout << "Vector: ";

	for (std::size_t i = 0; i < pairs.size(); ++i)
	{
		std::cout << "("
				  << _vector[pairs[i].small]
				  << ", "
				  << _vector[pairs[i].large]
				  << ")";

		if (i + 1 < pairs.size())
			std::cout << " ";
	}

    if (hasLeftover)
        std::cout << " (" << _vector[leftover] << ")";
	std::cout << std::endl;
}

// ------------------------------------------------ public functions ----------------------------------------------------

void PmergeMe::sort()
{
    std::cout << "Unsorted sequence (size: " << _vector.size() << "): " << this->getVector() <<  std::endl;

    clock_t start;
    clock_t end;

    start = clock();
    _sortVector();
    end = clock();
    double vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    start = clock();
    // _sortDeque(); // TODO
    end = clock();
    double dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Sorted sequence: " << this->getVector() <<  std::endl
              << "Vector sort time: " << vectorTime << "(ms)?" << std::endl 
              << "Deque sort time: " << dequeTime << "(ms)?" << std::endl;
}

const std::vector<int>& PmergeMe::getVector() const
{
    return this->_vector;
};

const std::deque<int>& PmergeMe::getDeque() const
{
    return this->_deque;
};

// ----------------------------------------------- private functions ---------------------------------------------------

void PmergeMe::_sortVector()
{
	std::vector<Pair> pairs; // pairs containing IDs - indexes - received by 
	std::vector<std::size_t> sortedIds; // sorted IDs
	std::vector<int> result;
	bool hasLeftover = false;
	std::size_t leftover;

	_initialPairingVector(pairs, hasLeftover, leftover); // prepare vector of pairs
	// _printPairsVector(pairs, hasLeftover, leftover);
	_sortVectorRecursion(pairs, hasLeftover, leftover, sortedIds); // recursion step - takes in vector of pairs and populates the vector of indexes of sorted numbers

	// Convert sorted IDs back to values.
	for (std::size_t i = 0; i < sortedIds.size(); ++i)
		result.push_back(_vector[sortedIds[i]]);
	_vector = result;
}

// prepare the numbers into pairs
void PmergeMe::_initialPairingVector(std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover)
{
	hasLeftover = false;

	for (std::size_t i = 0; i + 1 < _vector.size(); i += 2)
	{
		Pair pair;

		if (_vector[i] < _vector[i + 1])
		{
			pair.small = i + 0;
			pair.large = i + 1;
		}
		else
		{
			pair.small = i + 1;
			pair.large = i + 0;
		}

		pairs.push_back(pair);
	}

	if (_vector.size() % 2 != 0)
    {
		leftover = _vector.size() - 1;
        hasLeftover = true;
    }
}

// the recursive function
void PmergeMe::_sortVectorRecursion(const std::vector<Pair>& pairs, bool hasLeftover, std::size_t leftover, std::vector<std::size_t>& sortedIds)
{
    std::vector<std::size_t> largeIds; // find and store indexes of large element in pairs
	std::vector<Pair> nextPairs;       // pair large elements into new pairs and create a vector
	bool nextHasLeftover = false;
	std::size_t nextLeftover = 0;
	std::vector<std::size_t> sortedLargeIds; // sorted larger IDs - output after recursion escapes
	std::vector<Pair> sortedPairs;  // sorted pairs based on their large elements
    std::vector<std::size_t> mainChain;      // final main chain to which we push after recursion excapes and we put the elements back

	// 1. Base case
	if (pairs.empty())
	{
		if (hasLeftover) sortedIds.push_back(leftover);
		return;
	}

	// 2. Extract and pair large elements
	for (std::size_t i = 0; i < pairs.size(); ++i)
		largeIds.push_back(pairs[i].large);

	for (std::size_t i = 0; i + 1 < largeIds.size(); i += 2)
	{
		Pair pair;

		if (_vector[largeIds[i]] < _vector[largeIds[i + 1]])
		{
			pair.small = largeIds[i];
			pair.large = largeIds[i + 1];
		}
		else
		{
			pair.small = largeIds[i + 1];
			pair.large = largeIds[i];
		}

		nextPairs.push_back(pair);
	}

	if (largeIds.size() % 2 != 0)
	{
		nextHasLeftover = true;
		nextLeftover = largeIds.back();
	}

	// 3. Recursively sort pairs
	_sortVectorRecursion(nextPairs, nextHasLeftover, nextLeftover, sortedLargeIds);

	// 4. Reorder current pairs according to sorted large elements
	for (std::size_t i = 0; i < sortedLargeIds.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].large == sortedLargeIds[i])
			{
				sortedPairs.push_back(pairs[j]);
				break;
			}
		}
	}

	// 5. Build the main chain ( b1, a1, a2, a3, ... )
    // a is larger
    // b is smaller
	mainChain.push_back(sortedPairs[0].small);
	for (std::size_t i = 0; i < sortedPairs.size(); ++i)
		mainChain.push_back(sortedPairs[i].large);

	// 6. Insert the remaining small elements in Jacobsthal order (b3, b2, b5, b4, b11, b10, b9, ...)
	std::size_t previous = 1;
	std::size_t current = 3;

	while (previous < sortedPairs.size())
	{
		std::size_t upper = current;

		if (upper > sortedPairs.size())
			upper = sortedPairs.size();

		for (std::size_t i = upper; i > previous; --i)
		{
			std::size_t pairIndex = i - 1;

			std::size_t smallId = sortedPairs[pairIndex].small;
			std::size_t largeId = sortedPairs[pairIndex].large;

			// Find the position of a_i
			std::size_t largePosition = 0;

			while (largePosition < mainChain.size()
				&& mainChain[largePosition] != largeId)
			{
				++largePosition;
			}

			// Binary search only before a_i
			std::size_t left = 0;
			std::size_t right = largePosition;

			while (left < right)
			{
				std::size_t mid = left + (right - left) / 2;

				if (_vector[mainChain[mid]] < _vector[smallId])
					left = mid + 1;
				else
					right = mid;
			}

			mainChain.insert(
				mainChain.begin() + left,
				smallId);
		}

		// Next Jacobsthal number
		std::size_t next = current + 2 * previous;
		previous = current;
		current = next;
	}

	// 7. Insert the leftover with binary sort - leftover (b) has no corresponding a, so it can be inserted anywhere in the full chain.
	if (hasLeftover)
	{
		std::size_t left = 0;
		std::size_t right = mainChain.size();

		while (left < right)
		{
			std::size_t mid = left + (right - left) / 2;

			if (_vector[mainChain[mid]] < _vector[leftover])
				left = mid + 1;
			else
				right = mid;
		}

		mainChain.insert(mainChain.begin() + left, leftover);
	}

	// 9. Return the completely sorted IDs to the caller
	sortedIds = mainChain;
}
 

// ----------------------------------------- helper functions -------------------------------------------------



// PmergeMe::PmergeMe()
// {
//     throw std::runtime_error("Cannot instantiate with empty default constuctor. Aborting.");
// };

// PmergeMe::PmergeMe(const std::vector<int>  & container) : _container(container) {};

// PmergeMe::PmergeMe(const PmergeMe& origin) : _container(origin._container) {};

// PmergeMe& PmergeMe::operator =(const PmergeMe& origin)
// {
//     if (this != &origin)
//         std::cerr << "Cannot copy assign on class with const members. Returning without change." << std::endl;
//     return *this;
// };

// PmergeMe::~PmergeMe() {};

// std::ostream& operator <<(std::ostream& os, const PmergeMe& origin)
// {
//     const std::vector<int>& c = origin.getContainer();
//     for (std::vector<int>::const_iterator it = c.begin(); it != c.end(); ++it)
//         os << *it << " ";
//     return os;
// };

// const std::vector<int>  & PmergeMe::getContainer() const 
// {
//     return _container;
// };

// // ---------------------------------------------------- Algorithm -------------------------------------------------------------------------------------

// void PmergeMe::sort()
// {
//     if (_container.size() <= 3) return _sortThree();

//     int leftover = -1;
//     std::vector<Pair> pairContainer = _initialPairing(_container, leftover); // overrides leftover, if any
//     _container.clear(); // removes all elements
//     printPairsContainer(pairContainer, 0);
//     std::vector<std::vector<Pair>::iterator> main;
//     main.reserve(pairContainer.size());
//     for (std::vector<Pair>::iterator it = pairContainer.begin(); it != pairContainer.end(); ++it)
//         main.push_back(it);  
//     _mergeInsertion(main, leftover);
// }; 

// void    PmergeMe::_sortThree()
// {
//     std::vector<int>::iterator it = _container.begin();
//     if (_container.size() <= 1)
//         return ;
//     if (_container.size() == 2)
//     {
//         if (*it > *(it + 1)) std::iter_swap(it, it + 1);
//         return ;
//     }
//     if (*(it + 1) > *(it + 2)) std::iter_swap(it + 1, it + 2);
//     if (*(it) > *(it + 2)) std::iter_swap(it, it + 2);
//     if (*it > *(it + 1)) std::iter_swap(it, it + 1);
// };

// std::vector<Pair> PmergeMe::_initialPairing(std::vector<int>& container, int& leftover)
// {
//     std::vector<Pair> pairedContainer;
    
//     pairedContainer.reserve((container.size() + 1) / 2);
//     std::vector<int>::iterator it;
//     for (it = container.begin(); it != container.end() && it + 1 !=  container.end(); ++it)
//     {
//         if (*it > *(it + 1))
//             std::iter_swap(it, it + 1); // swap pairs if needed
//         pairedContainer.push_back(std::make_pair(*it, *(it + 1)));
//         it += 1;
//     }
//     if (it != container.end())
//         leftover = *it;
//     return pairedContainer;
// };

// // 1. the pairContainer has pairs
// // 2. first main stores iterators to these pairs in pairContainer
// // 3. create new main from larger elements -> this new main stores iterators of teh larger elements and put it to recursion as input variable
// // 4. again create new main from larger elements and put it to recursion
// // 5. the base case is hit - put the element into resulting vector of pointers 
// // 6. go to the previous level - iterate the input container (for now from start) and call binary search on the dereferenced iterator's smaller element to put it to resultnig container, using the iterator as bounding element, and put entire iterator here


// // maybe this is not optimal since it first must find the upperBound by making comparisons ? 
// void PmergeMe::_binaryInsertion(std::vector<Pair>& to, std::vector<Pair>::iterator& toInsert, std::vector<Pair>::iterator& upperBound)
// {
//     std::vector<Pair>::iterator low = to.begin();
//     std::vector<Pair>::iterator high = upperBound;
//     int value = (*toInsert).first;
//     std::cout << "Binary insert: " << value << " with upper bound at " << (*high).second << std::endl;
//     // binary search
//     while ((*low).second < (*high).second)
//     {
//         std::vector<Pair>::iterator mid = low + (high - low) / 2; // for even numbers it selects the left(first,sooner) one as middle
//         if ((*mid).second < value)
//             low = mid + 1;
//         else
//             high = mid;
//     }
//     sortedContainer.insert(low, toInsert);
// };

// // TODO !!!
// void getNextJacobsthalEl(std::vector<Pair>::iterator& toInsert, std::vector<Pair>& pairContainer, int& prevJacobsthal, int& index)
// {
//     // not using jacobsthal but going from beginning
//     (void)pairContainer;
//     (void)index;
//     (void)prevJacobsthal;
//     ++toInsert;

   
// };

// // takes in vector of iterators
// void PmergeMe::_mergeInsertion(std::vector<Pair*>& input, int& leftover)
// {
//     // debug
//     std::cout << "INPUT: ";
//     printPairsContainer(input, 1);
//     if (leftover > 0) std::cout << " ( leftover " << leftover << ")" << std::endl;
//     else std::cout << " ( leftover none )" << std::endl;

//     // BASE CASE - must be before recustion call so we can actually escape
//     if (input.size() <= 1)
//     {
//         return ;
//     }

//     // create main from larger elements for next recursion step
//     std::vector<Pair*>::iterator it1;
//     std::vector<Pair*> main;
//     for (it1 = input.begin(); it1 != input.end() && it1 + 1 !=  input.end(); ++it1)
//     {
//         // if elements in the pair are not in order, swap their values
//         if ((*it1).second > (*(it1 + 1)).second)
//             std::iter_swap(it1, it1 + 1);
//         main.push_back(std::make_pair((*it1).second, (*(it1 + 1)).second));
//         it1 += 1; // protect against odd input - leftover
//     }
//     int newLeftover = (it1 != pairContainer.end()) ? (*it1).second : -1; // store leftover, if any, so we can insert it

//     // recurse on main
//     _mergeInsertion(sortedContainer, main, newLeftover); // the elements from main are already in in sorted sequence, pass in leftover without storing it 

//     std::vector<Pair*>::iterator it2 = input.begin();
//     while (it2 != input.end())
//     {
//             _binaryInsert(main, *(it2), it2);
//             it2++;
//     }

//     if (leftover > -1)
//         _binaryInsertion(main, std::make_pair(-1, leftover), main.end()); // when inserting leftovers, if it is larger than teh max element, it would never get to back becasue last el is largest and set as upper bound - set this leftover el as upperbound instead
// };