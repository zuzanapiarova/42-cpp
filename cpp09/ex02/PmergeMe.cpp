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
    _sortDeque();
    end = clock();
    double dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Sorted sequence (vector): " << this->getVector() <<  std::endl;
    std::cout << "Sorted sequence (deque): " << this->getDeque() <<  std::endl;
    std::cout << "Vector sort time: " << vectorTime << " microseconds" << std::endl;
    std::cout << "Deque sort time: " << dequeTime << " microseconds" << std::endl;
}

const std::vector<int>& PmergeMe::getVector() const
{
    return this->_vector;
};

const std::deque<int>& PmergeMe::getDeque() const
{
    return this->_deque;
};

// ----------------------------------------------- private functions - vector ---------------------------------------------------

void PmergeMe::_sortVector()
{
    std::vector<Pair>           pairs;
    std::vector<std::size_t>    sortedIds;
    std::vector<int>            result;
    std::vector<std::size_t>    indices;
    bool                        hasLeftover = false;
    std::size_t                 leftover = 0;

    // optimization so vector know how large it will be and does not realocate
    indices.reserve(_vector.size());
    pairs.reserve(_vector.size() / 2);
    sortedIds.reserve(_vector.size());
    result.reserve(_vector.size());

    for (std::size_t i = 0; i < _vector.size(); ++i)
        indices.push_back(i);

    _makeIndexPairs(indices, pairs, hasLeftover, leftover);
    _sortRecursion(pairs, hasLeftover, leftover, sortedIds);

    for (std::size_t i = 0; i < sortedIds.size(); ++i)
        result.push_back(_vector[sortedIds[i]]);

    _vector = result;
}

// prepare the numbers into pairs and sort them in-pair
void PmergeMe::_makeIndexPairs(const std::vector<std::size_t>& indices, std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover)
{
    hasLeftover = false;
    pairs.reserve(pairs.size() + indices.size() / 2);

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
void PmergeMe::_sortRecursion(const std::vector<Pair>& pairs, bool hasLeftover, std::size_t leftover, std::vector<std::size_t>& sortedIds)
{
    std::vector<std::size_t>  larges;
    std::vector<Pair>         nextPairs;
    std::vector<std::size_t>  sortedLarges;
    std::vector<Pair>         sortedPairs;
    std::vector<std::size_t>  mainChain;

    bool nextHasLeftover = false;
    std::size_t nextLeftover = 0;

    if (pairs.empty())
    {
        if (hasLeftover)
            sortedIds.push_back(leftover);
        return;
    }

    // optimization
    larges.reserve(pairs.size());
    nextPairs.reserve(pairs.size() / 2);
    sortedLarges.reserve(pairs.size());
    sortedPairs.reserve(pairs.size());
    mainChain.reserve(pairs.size() * 2);

    // 1. Extract the large elements.
    for (std::size_t i = 0; i < pairs.size(); ++i)
        larges.push_back(pairs[i].large);

    // 2. Pair the large elements and recurse.
    _makeIndexPairs(larges, nextPairs, nextHasLeftover, nextLeftover);
    _sortRecursion(nextPairs, nextHasLeftover, nextLeftover, sortedLarges);

    // 3. Reorder the pairs to match sorted order - now pairs are sorted based on their large
    std::vector<Pair> pairByLarge(_vector.size()); // lookup table with O(1)
    for (std::size_t i = 0; i < pairs.size(); ++i)
        pairByLarge[pairs[i].large] = pairs[i];

    for (std::size_t i = 0; i < sortedLarges.size(); ++i)
        sortedPairs.push_back(pairByLarge[sortedLarges[i]]);

    // 4. Build main chain: b1, a1, a2, a3, ... - a is larger, b is smaller
    mainChain.push_back(sortedPairs[0].small); // b1
    for (std::size_t i = 0; i < sortedPairs.size(); ++i)
        mainChain.push_back(sortedPairs[i].large);

    // NEW: positionOf[largeId] = that large element's current index inside
    // mainChain. Indexed directly by the original array index (same trick as
    // pairByLarge above), so it's an O(1) read instead of a scan. levelLarges
    // is just the list of ids we're allowed to touch when we maintain it.
    std::vector<std::size_t> levelLarges(sortedPairs.size());
    std::vector<std::size_t> positionOf(_vector.size());
    for (std::size_t i = 0; i < sortedPairs.size(); ++i)
    {
        levelLarges[i] = sortedPairs[i].large;
        positionOf[sortedPairs[i].large] = i + 1; // +1: b1 occupies index 0
    }

    // 5. Insert remaining small elements in Jacobsthal order
    std::size_t previous = 1;
    std::size_t current = 3;
    while (previous < sortedPairs.size())
    {
        std::size_t upper = current;
        if (upper > sortedPairs.size()) upper = sortedPairs.size();

        for (std::size_t i = upper; i > previous; --i)
            _insertSmall(mainChain, sortedPairs[i - 1], positionOf, levelLarges);

        std::size_t next = current + 2 * previous; // find next Jacobsthal number
        previous = current;
        current = next;
    }

    // 6. Insert leftover
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

    sortedIds = mainChain;
}

// smaller element is inserted by binary sort between the beginning and its large
void PmergeMe::_insertSmall(std::vector<std::size_t>& mainChain, const Pair& pair, std::vector<std::size_t>& positionOf, const std::vector<std::size_t>& levelLarges)
{
    std::size_t smallId = pair.small;
    std::size_t largeId = pair.large;

    // O(1) lookup - no more scanning mainChain for largeId.
    std::size_t largePosition = positionOf[largeId];

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

    // Everything that was at or after the insertion point just shifted right by one.
    for (std::size_t i = 0; i < levelLarges.size(); ++i)
        if (positionOf[levelLarges[i]] >= left)
            positionOf[levelLarges[i]] += 1;
}

// ----------------------------------------------- private functions - deque ---------------------------------------------------

void PmergeMe::_sortDeque()
{
    std::deque<Pair>           pairs;
    std::deque<std::size_t>    sortedIds;
    std::deque<int>            result;
    std::deque<std::size_t>    indices;
    bool                       hasLeftover = false;
    std::size_t                leftover = 0;

    for (std::size_t i = 0; i < _deque.size(); ++i)
        indices.push_back(i);

    _makeIndexPairs(indices, pairs, hasLeftover, leftover);
    _sortRecursion(pairs, hasLeftover, leftover, sortedIds);

    for (std::size_t i = 0; i < sortedIds.size(); ++i)
        result.push_back(_deque[sortedIds[i]]);

    _deque = result;
}


// prepare the numbers into pairs and sort them in-pair
void PmergeMe::_makeIndexPairs(const std::deque<std::size_t>& indices, std::deque<Pair>& pairs, bool& hasLeftover, std::size_t& leftover)
{
    hasLeftover = false;

    for (std::size_t i = 0; i + 1 < indices.size(); i += 2)
    {
        Pair pair;

        if (_deque[indices[i]] < _deque[indices[i + 1]])
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


// the recursive function - takes in deque of pairs and populates the deque with indexes of sorted numbers
void PmergeMe::_sortRecursion(const std::deque<Pair>& pairs, bool hasLeftover, std::size_t leftover, std::deque<std::size_t>& sortedIds)
{
    std::deque<std::size_t> larges;
    std::deque<Pair>        nextPairs;
    std::deque<std::size_t> sortedLarges;
    std::deque<Pair>        sortedPairs;
    std::deque<std::size_t> mainChain;

    bool nextHasLeftover = false;
    std::size_t nextLeftover = 0;

    if (pairs.empty())
    {
        if (hasLeftover)
            sortedIds.push_back(leftover);
        return;
    }

    // 1. Extract the large elements.
    for (std::size_t i = 0; i < pairs.size(); ++i)
        larges.push_back(pairs[i].large);

    // 2. Pair the large elements and recurse.
    _makeIndexPairs(larges, nextPairs, nextHasLeftover, nextLeftover);
    _sortRecursion(nextPairs, nextHasLeftover, nextLeftover, sortedLarges);

    // 3. Reorder pairs using the large element ID as the lookup key.
    std::deque<Pair> pairByLarge(_deque.size()); // lookup table with O(1)

    for (std::size_t i = 0; i < pairs.size(); ++i)
        pairByLarge[pairs[i].large] = pairs[i];

    for (std::size_t i = 0; i < sortedLarges.size(); ++i)
        sortedPairs.push_back(pairByLarge[sortedLarges[i]]);

    // 4. Build main chain: b1, a1, a2, a3, ...
    mainChain.push_back(sortedPairs[0].small);

    for (std::size_t i = 0; i < sortedPairs.size(); ++i)
        mainChain.push_back(sortedPairs[i].large);

    // NEW: same O(1) position tracking as the vector version.
    std::vector<std::size_t> levelLarges(sortedPairs.size());
    std::vector<std::size_t> positionOf(_deque.size());
    for (std::size_t i = 0; i < sortedPairs.size(); ++i)
    {
        levelLarges[i] = sortedPairs[i].large;
        positionOf[sortedPairs[i].large] = i + 1;
    }

    // 5. Insert remaining small elements in Jacobsthal order.
    std::size_t previous = 1;
    std::size_t current = 3;

    while (previous < sortedPairs.size())
    {
        std::size_t upper = current;

        if (upper > sortedPairs.size())
            upper = sortedPairs.size();

        for (std::size_t i = upper; i > previous; --i)
            _insertSmall(mainChain, sortedPairs[i - 1], positionOf, levelLarges);

        std::size_t next = current + 2 * previous;
        previous = current;
        current = next;
    }

    // 6. Insert odd leftover.
    if (hasLeftover)
    {
        std::size_t left = 0;
        std::size_t right = mainChain.size();

        while (left < right)
        {
            std::size_t mid = left + (right - left) / 2;

            if (_deque[mainChain[mid]] < _deque[leftover])
                left = mid + 1;
            else
                right = mid;
        }

        mainChain.insert(mainChain.begin() + left, leftover);
    }

    sortedIds = mainChain;
}
void PmergeMe::_insertSmall(std::deque<std::size_t>& mainChain, const Pair& pair, std::vector<std::size_t>& positionOf, const std::vector<std::size_t>& levelLarges)
{
    std::size_t smallId = pair.small;
    std::size_t largeId = pair.large;

    std::size_t largePosition = positionOf[largeId];

    std::size_t left = 0;
    std::size_t right = largePosition;

    while (left < right)
    {
        std::size_t mid = left + (right - left) / 2;

        if (_deque[mainChain[mid]] < _deque[smallId])
            left = mid + 1;
        else
            right = mid;
    }

    mainChain.insert(mainChain.begin() + left, smallId);

    for (std::size_t i = 0; i < levelLarges.size(); ++i)
        if (positionOf[levelLarges[i]] >= left)
            positionOf[levelLarges[i]] += 1;
}