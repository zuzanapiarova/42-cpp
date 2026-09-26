#pragma once

# include <iostream>
# include <vector>
# include <deque>
# include <utility>
# include <ctime>

#include <string>
#include <exception>
#include <istream>
#include <limits>
#include <cerrno>
#include <algorithm>

// so that Pair can be written instead of std::pair<int, int>
// stores IDs, not values
struct Pair
{
	std::size_t small; // index in _vector
	std::size_t large; // index in _vector
};

// element keeps the pairs even through recursion to know which element was with which after sorting the larger ones 
// struct Element
// {
// 	int value;
// 	Element* partner;
// };
// typedef std::pair<int, int> Pair;

// helpers
bool safeStrToPositiveInt(const char* str, int& result);
// int     nearestLowerPowerOf2(int size);
// int     calculateMaxNumberOfComparisons(int n);
// int     getNextJacobsthal(int previousJacobsthal);

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::deque<int>  _deque;

		// Vector implementation
		void _sortVector();
		void _initialPairingVector(std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover);
		void _sortVectorRecursion(const std::vector<Pair>& pairs, bool hasLeftover, std::size_t leftover, std::vector<std::size_t>& result);
        void _printPairsVector(const std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover);

		// Deque implementation
		// void _sortDeque();
		// void _initialPairingDeque(std::deque<Pair>& pairs, int& leftover);
		// void _mergeInsertionDeque(std::deque<Pair>& pairs, int leftover);

	public:
		PmergeMe();
		PmergeMe(const std::vector<int>& vector, const std::deque<int>& deque);
		PmergeMe(const PmergeMe& origin);
		PmergeMe& operator=(const PmergeMe& origin);
		~PmergeMe();

		void sort();

		const std::vector<int>& getVector() const;
		const std::deque<int>& getDeque() const;
};

std::ostream& operator<<(std::ostream& os, const PmergeMe& pmergeMe);

std::ostream& operator<<(std::ostream& os, const std::vector<int>& container); // print vector
std::ostream& operator<<(std::ostream& os, const std::deque<int>& container); // print deque

std::ostream& operator<<(std::ostream& os, const std::vector<Pair>& container); // print vector