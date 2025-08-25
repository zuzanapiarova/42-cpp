# pragma once


#include <string>
#include <iostream>
#include <exception>
#include <cerrno>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>

// struct to store pairs of loser-winnerPtr
struct Pair
{
    int value;
    Pair* winnerPtr;

    Pair(int v) : value(v), winnerPtr(NULL) {};

};

// helpers.cpp
bool                safeStrToPositiveInt(const char* str, int &res);
int                 nearestLowerPowerOf2(int size);
int                 calculateMaxNumberOfComparisons(int n);
int                 getNextJacobsthal(int previousJacobsthal);
std::vector<int>    populateContainer(int size, char **arguments);
void                printPairsContainer(std::vector<Pair*> container);

class PmergeMe
{
    private:
        std::vector<int>      _container;

        void                                _sortThree();
        std::vector<Pair*>                  _initialPairing(std::vector<int>& _container);
        std::vector<Pair*>                    _mergeInsertion(std::vector<Pair*>& sortedContainer);
        void                                _binaryInsertion(std::vector<Pair*>& result, Pair* value);
    
    public:
        PmergeMe();
        PmergeMe(const std::vector<int>& vector);
        PmergeMe(const PmergeMe& origin);
        PmergeMe& operator =(const PmergeMe& origin);
        ~PmergeMe();
    
        void sort();
        const std::vector<int>& getContainer() const ;
};

std::ostream& operator <<(std::ostream& os, const PmergeMe& origin);

