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

std::vector<int>   populateContainer(int size, char **arguments);

class PmergeMe
{
    private:
        std::vector<int>      _container;
        std::vector<int>      _sorted;

        void                                _binaryInsertion(std::vector<int>& sortedContainer, int value, int upperBound);
        void                                _mergeInsertion(std::vector<int>& sortedContainer, std::vector<std::pair<int, int> >& pairContainer, int& leftover);
        std::vector<std::pair<int, int> >   _initialPairing(std::vector<int>& _container, int& leftover);
        void                                _createMain(std::vector<std::pair<int,int> >& pairContainer, std::vector<std::pair<int,int> >& main, std::vector<std::pair<int,int> >::iterator& it1);

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

