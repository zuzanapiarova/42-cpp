#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    // std::cout << "PmergeMe default constructor called." << std::endl;
    _v = 
    _d = 
};

PmergeMe::PmergeMe(const PmergeMe& origin) : _v(origin._v), _d(origin._d)
{
    // std::cout << "PmergeMe copy constructor called." << std::endl;
};
PmergeMe& PmergeMe::operator =(const PmergeMe& origin)
{
    // std::cout << "PmergeMe copy constructor called." << std::endl;
    if (this != &origin)
    {
        _v = origin._v;
        _d = origin._d;
    }
    return *this;
};

PmergeMe::~PmergeMe()
{
    // std::cout << "PmergeMe destructor called." << std::endl;
};

bool safeStrToInt(const char* str, int &res)
{
    errno = 0;
    char *endptr;
    long val = std::strtol(str, &endptr, 10);
    if (*endptr != '\0') return false; 
    if ((errno == ERANGE) || val > INT_MAX || val < INT_MIN) return false; // check for overflow or out of int
    res = static_cast<int>(val);
    return true;
}

void PmergeMe::populateVector(int size, char **members)
{
    int num;

    for (int i = 1; i < size; ++i)
    {
        if (safeStrToInt(members[i], num))
            _v.push_back(num);
        else
            throw std::runtime_error("Invalid argument.");
    }
};

void PmergeMe::populateDeque(int size, char **members)
{
    int num;

    for (int i = 1; i < size; ++i)
    {
        if (safeStrToInt(members[i], num))
            _d.push_back(num);
        else
            throw std::runtime_error("Invalid argument.");
    }

};

void PmergeMe::mergeInsertVector()
{

};

void PmergeMe::mergeInsertDeque()
{

};