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
};

int nearestLowerPowerOf2(int size)
{
    if (size < 1)
        return 0;

    int res = 1;    
    while (size > res*2)
        res *= 2;
    return res;
}