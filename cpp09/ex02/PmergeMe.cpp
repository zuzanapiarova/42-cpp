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

bool safeStrToUnsignedInt(const char* str, unsigned int &res)
{
    errno = 0;
    char *endptr;
    unsigned long val = strtoul(str, &endptr, 10);
    if (*endptr != '\0') return false; 
    if ((errno == ERANGE) || val > std::numeric_limits<unsigned int>::max() || val < std::numeric_limits<unsigned int>::min()) return false; // check for overflow or out of int
    res = static_cast<unsigned int>(val);
    return true;
}

std::vector<unsigned int> populateVector(int size, char **arguments)
{
    unsigned int                 num;
    std::vector<unsigned int>    v;

    for (int i = 1; i < size; ++i)
    {
        if (!safeStrToUnsignedInt(arguments[i], num)) throw std::runtime_error("Invalid argument.");
        v.push_back(num);
    }
    return v;
};

std::deque<unsigned int> populateDeque(int size, char **arguments)
{
    unsigned int             num;
    std::deque<unsigned int> d;

    for (int i = 1; i < size; ++i)
    {
        if (!safeStrToUnsignedInt(arguments[i], num)) throw std::runtime_error("Invalid argument.");
        d.push_back(num);
    }
    return d;
};