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
    while (size >= res*2)
        res *= 2;
    return res;
};

int calculateMaxNumberOfComparisons(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k)
    {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
};

int getNextJacobsthal(int previousJacobsthal)
{
    if (previousJacobsthal < 0) return 0;
    if (previousJacobsthal < 1) return 1;
    
    int result;
    int a = 0;
    int b = 1;

    while (a < previousJacobsthal)
    {
        int next = b + 2*a;
        a = b;
        b = next;
    }
    return b;
}