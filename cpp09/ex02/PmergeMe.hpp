# pragma once

#include <iostream>
#include <string>
#include <exception>
#include <istream>
#include <limits>
#include <cerrno>
#include <algorithm>
#include <vector>
#include <deque>
#include <utility>

typedef std::pair<int,int> Pair;

// helpers.cpp
bool safeStrToPositiveInt(const char* str, int &res);
int nearestLowerPowerOf2(int size);
int calculateMaxNumberOfComparisons(int n);
int getNextJacobsthal(int previousJacobsthal);
std::vector<int>   populateContainer(int size, char **arguments);
void printPairsContainer(std::vector<std::pair<int, int> >& container, bool onlyLarge);

class PmergeMe
{
    private:
        std::vector<int>      _container;

        void                                _binaryInsertion(std::vector<Pair>& to, std::vector<Pair>::iterator& toInsert, std::vector<Pair>::iterator& upperBound);
        void                                _mergeInsertion(std::vector<std::vector<Pair>::iterator>& input, int& leftover);
        std::vector<std::pair<int, int> >   _initialPairing(std::vector<int>& _container, int& leftover);
        void                                _sortThree();
   
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

