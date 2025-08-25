#include "PmergeMe.hpp"

#include <string>
#include <iostream>
#include <exception>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream> // string streams

bool safeStrToPositiveInt(const char* str, int &res)
{
    std::istringstream iss(str); // string stream is only safe and standard way to convert strings to numbers in c++98
    iss >> res; // reads input from string and checks for integer format and range
    if (iss.fail() || !iss.eof()) throw std::invalid_argument("Invalid integer input."); // iss sets flags if reading from string goes wrong
    if (res < 0 || res > std::numeric_limits<int>::max()) throw std::out_of_range("Value outside of unsigned int not allowed."); // we only want positive integers
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
    if (previousJacobsthal == 1)
        return 3;
    if (previousJacobsthal < 0) return 0;
    if (previousJacobsthal < 1) return 1;
    
    int a = 0;
    int b = 1;

    while (a < previousJacobsthal)
    {
        int next = b + 2 * a;
        a = b;
        b = next;
    }
    return b;
}

std::vector<int>   populateContainer(int size, char **arguments)
{
    int                 num;
    std::vector<int>    c;

    for (int i = 1; i < size; ++i)
    {
        if (arguments[i] == NULL || arguments[i][0] == '\0') throw std::runtime_error("Invalid argument.");
        if (!safeStrToPositiveInt(arguments[i], num)) throw std::runtime_error("Invalid argument.");
        if (std::find(c.begin(), c.end(), num) != c.end()) throw std::runtime_error("Duplicate arguments.");
        c.push_back(num);
    }
    return c;
};

void printPairsContainer(std::vector<Pair*> container)
{
    for (std::vector<Pair*>::iterator it = container.begin(); it != container.end(); it++)
    {
        std::cout << (*(*it)).value << " ";
        // if ((*it).winnerPtr)
        //     std::cout << "(" << (*(*it).winnerPtr).value << ")";
    }
    std::cout << std::endl;
}