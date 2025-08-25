#include "PmergeMe.hpp"

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

    // make initial 
    std::vector<Pair*> input = _initialPairing(_container); // overrides leftover, if any
    std::vector<Pair*> result = _mergeInsertion(input);
    // cleanup
    for (std::vector<Pair*>::iterator it = input.begin(); it != input.end(); ++it)
    {
        delete *it;
    }
    _container.clear();
    std::cout << "Finished" << std::endl;
    // populate container back
    for (std::vector<Pair*>::iterator it = result.begin(); it != result.end(); ++it)
    {
        Pair* el = *it;
        int value = (*el).value;
        std::cout << value << std::endl;
        _container.push_back((*(*it)).value);
    }
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

// create initial Pair* container from int container, where pair.value=int and pair.winner=NULL
std::vector<Pair*> PmergeMe::_initialPairing(std::vector<int>& container)
{
    std::vector<Pair*> pairedContainer;
    for (std::vector<int>::iterator it = container.begin(); it != container.end(); ++it)
    {
        Pair* pair = new Pair(*it);
        pairedContainer.push_back(pair);
    }
    return pairedContainer;
};

// _binaryInsertion(result, pend[i], pend[i]->winnerPtr);
void PmergeMe::_binaryInsertion(std::vector<Pair*>& result, Pair* toInsert)
{
    std::cout << "Binary insert: " << (*toInsert).value << " with upper bound " << (*(*toInsert).winnerPtr).value << std::endl;

    std::vector<Pair*>::iterator low = result.begin();
    std::vector<Pair*>::iterator high = result.begin();
    while (*high != (*toInsert).winnerPtr) // cannot use this here because iterator in a container is not a pointer
        high++;
    while ((*(*low)).value < (*(*high)).value)
    {
        std::vector<Pair*>::iterator mid = low + (high - low) / 2; // for even numbers it selects the left(first,sooner) one as middle
        if ((*(*mid)).value < (*toInsert).value)
            low = mid + 1;
        else
            high = mid;
    }
    result.insert(low, toInsert);
};

std::vector<Pair*> PmergeMe::_mergeInsertion(std::vector<Pair*>& input)
{
    // debug
    std::cout << "INPUT: ";
    printPairsContainer(input);

    // BASE CASE - must be before recustion call so we can actually escape
    // starts the resulting list of Pair pointers
    if (input.size() <= 1)
    {
        return std::vector<Pair*>(input.begin(), input.end());
    }

    // make main and pend
    std::vector<Pair*> main;
    std::vector<Pair*> pend;
    // always create new pair from adjacent elements, swap if needed, and 
    for (size_t i = 0; i + 1 < input.size(); i += 2)
    {
        Pair* a = input[i]; // smaller
        Pair* b = input[i + 1]; // larger
        if (a->value > b->value) std::swap(a,b); // ? does this swap their values or the pointers ? 
        b->winnerPtr = NULL;
        a->winnerPtr = b;
        main.push_back(b);
        pend.push_back(a);
    }
    if (input.size() % 2 == 1) // if one is leftover, put it to main with winnerPtr as NULL
    {
        Pair* leftover = input.back();
        main.push_back(leftover); // !  --> LATER change this as leftover is supposed to be in pend, not it main
    }

    // recurse on main. result is sorted list of Pair*
    std::vector<Pair*> result = _mergeInsertion(main); // the elements from main are already in in sorted sequence, pass in leftover without storing it 

    // put back pend to result
    for (size_t i = 0; i < pend.size(); i++)
    {
        _binaryInsertion(result, pend[i]);
    }

    return result;
};