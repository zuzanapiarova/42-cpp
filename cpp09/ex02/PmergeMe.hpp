#pragma once

# include <iostream>
# include <vector>
# include <deque>
# include <utility>
# include <ctime>

#include <string>
#include <sstream>
#include <istream>
#include <exception>
#include <limits>
#include <cerrno>
#include <algorithm>
#include <cmath>

// Pair stores indexes of the smaller and larger element in the initial unsorted container, not their values
struct Pair
{
	std::size_t small; // index in initial sequence
	std::size_t large; // index in initial sequence
};

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::deque<int>  _deque;

		// Vector implementation
		void _sortVector();
		void _makeIndexPairsVector(const std::vector<std::size_t>& indices, std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover);
		void _sortVectorRecursion(const std::vector<Pair>& pairs, bool hasLeftover, std::size_t leftover, std::vector<std::size_t>& sortedIds);
        void _printPairsVector(const std::vector<Pair>& pairs, bool& hasLeftover, std::size_t& leftover);
		void _insertSmall(std::vector<std::size_t>& mainChain, const Pair& pair);

		// Deque implementation
		void _sortDeque();
		void _makeeIndexPairsDeque(std::deque<Pair>& pairs, int& leftover);
		void _mergeInsertionDeque(std::deque<Pair>& pairs, int leftover);

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

std::ostream& operator<<(std::ostream& os, const std::vector<int>& container); // print vector
std::ostream& operator<<(std::ostream& os, const std::deque<int>& container); // print deque

std::ostream& operator<<(std::ostream& os, const std::vector<Pair>& container); // print pair vector