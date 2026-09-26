#include "PmergeMe.hpp"

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

    std::cout << "Sorted sequence: " << this->getVector() <<  std::endl;
    std::cout << "Vector sort time: " << vectorTime << "(ms)?" << std::endl;
    std::cout << "Deque sort time: " << dequeTime << "(ms)?" << std::endl;
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
	std::vector<Pair>           pairs;      // vector of pairs of indexes of larger and smaller elements, sorted in-pair
	std::vector<std::size_t>    sortedIds;  // vector of sorted IDs
	std::vector<int>            result;
	bool                        hasLeftover = false;
	std::size_t                 leftover;

    std::vector<std::size_t>    indices; // turn vector of pairs to initially into a vector of indexes
    for (std::size_t i = 0; i < _vector.size(); ++i)
        indices.push_back(i);

	_makeIndexPairsVector(indices, pairs, hasLeftover, leftover); // prepare vector of sorted pairs, check and save if has leftover
	_sortVectorRecursion(pairs, hasLeftover, leftover, sortedIds); // recursion step

	// Convert sorted IDs back to values
	for (std::size_t i = 0; i < sortedIds.size(); ++i)
		result.push_back(_vector[sortedIds[i]]);
	_vector = result;
}

// prepare the numbers into pairs and sort them in-pair
void PmergeMe::_makeIndexPairsVector(const std::vector<std::size_t>& indices, std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover)
{
    hasLeftover = false;

    for (std::size_t i = 0; i + 1 < indices.size(); i += 2)
    {
        Pair pair;

        if (_vector[indices[i]] < _vector[indices[i + 1]])
        {
            pair.small = indices[i];
            pair.large = indices[i + 1];
        }
        else
        {
            pair.small = indices[i + 1];
            pair.large = indices[i];
        }

        pairs.push_back(pair);
    }

    if (indices.size() % 2 != 0)
    {
        hasLeftover = true;
        leftover = indices.back();
    }
}

// the recursive function - takes in vector of pairs and populates the vector with indexes of sorted numbers
void PmergeMe::_sortVectorRecursion(const std::vector<Pair>& pairs, bool hasLeftover, std::size_t leftover, std::vector<std::size_t>& sortedIds)
{
    std::vector<std::size_t> larges;   // indexes of large element in pairs
	std::vector<Pair> nextPairs;       // new pairs of large elements into new pairs and create a vector
	bool nextHasLeftover = false;
	std::size_t nextLeftover = 0;
	std::vector<std::size_t> sortedLarges; // sorted larger IDs - output after recursion escapes
	std::vector<Pair> sortedPairs;  // sorted pairs based on their large elements
    std::vector<std::size_t> mainChain;      // final main chain to which we push after recursion excapes and we put the elements back

	// 1. Base case
	if (pairs.empty())
	{
		if (hasLeftover) sortedIds.push_back(leftover);
		return;
	}

	// 2. Extract, pair, and sort large elements into new pairs vector
    for (std::size_t i = 0; i < pairs.size(); ++i)
        larges.push_back(pairs[i].large);
    _makeIndexPairsVector(larges, nextPairs, nextHasLeftover, nextLeftover);

	// 3. Recursively call the unction on the new vector of pairs
	_sortVectorRecursion(nextPairs, nextHasLeftover, nextLeftover, sortedLarges);

	// 4. Reorder current pairs according to sorted large elements - entire pairs are now sorted based on their large element
	for (std::size_t i = 0; i < sortedLarges.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].large == sortedLarges[i])
			{
				sortedPairs.push_back(pairs[j]);
				break;
			}
		}
	}

	// 5. Build the main chain ( b1, a1, a2, a3, ... ), a is larger, b is smaller
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
            _insertSmall(mainChain, sortedPairs[i - 1]);

        std::size_t next = current + 2 * previous; // find next Jacobsthal number
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

// ---------------------------------------------------------- helpers ----------------------------------------------------------

void PmergeMe::_insertSmall(std::vector<std::size_t>& mainChain, const Pair& pair)
{
    std::size_t smallId = pair.small;
    std::size_t largeId = pair.large;

    // Find the position of the corresponding large element
    std::size_t largePosition = 0;

    while (largePosition < mainChain.size() && mainChain[largePosition] != largeId)
    {
        ++largePosition;
    }

    // Binary search only before the large element
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

    mainChain.insert(mainChain.begin() + left, smallId);
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