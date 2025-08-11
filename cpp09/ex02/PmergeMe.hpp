# pragma once

#include <iostream>
#include <string>
#include <exception>
#include <istream>
#include <algorithm>
#include <vector>
#include <deque>

class PmergeMe
{
    private:
        std::vector<unsigned int>   _v;
        std::deque<unsigned int>    _d;

    public:
        PmergeMe();
        PmergeMe(const std::string& input);
        PmergeMe(const PmergeMe& origin);
        PmergeMe& operator =(const PmergeMe& origin);
        ~PmergeMe();
    
        void populateVector(int size, char **members);
        void populateDeque(int size, char **members);
        void mergeInsertVector();
        void mergeInsertDeque();

};