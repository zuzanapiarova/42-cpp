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

template <typename Container>
class PmergeMe
{
    private:
        Container _container;

    public:
        PmergeMe();
        PmergeMe(const Container& container);
        PmergeMe(const PmergeMe& origin);
        PmergeMe& operator =(const PmergeMe& origin);
        ~PmergeMe();
    
        void sort();

};

