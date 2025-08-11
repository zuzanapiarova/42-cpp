#include "PmergeMe.hpp"

template <typename Container>
PmergeMe<Container>::PmergeMe()
{
    // std::cout << "PmergeMe default constructor called." << std::endl;
    throw std::runtime_error("Cannot instantiate with empty default constuctor. Aborting.");
};

template <typename Container>
PmergeMe<Container>::PmergeMe(const Container& container) : _container(container)
{
    // std::cout << "PmergeMe default constructor called." << std::endl;
    throw std::runtime_error("Cannot instantiate with empty default constuctor. Aborting.");
};

template <typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe& origin) : _container(origin._container)
{
    // std::cout << "PmergeMe copy constructor called." << std::endl;
};

template <typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator =(const PmergeMe& origin)
{
    // std::cout << "PmergeMe copy constructor called." << std::endl;
    if (this != &origin)
        _container = origin._container;
    return *this;
};

template <typename Container>
PmergeMe<Container>::~PmergeMe()
{
    // std::cout << "PmergeMe destructor called." << std::endl;
};

// template<> means is explicit template specialization
//  empty angle brackets <> mean it is no longer a template definition for a generic T, but that the type parameters are already fixed, in this case to either vector or deque, and that it will be the one exact, concrete version of that function
template <>
void PmergeMe<std::vector<unsigned int> >::sort()
{
    _container.push_back(1);
};

template <>
void PmergeMe<std::deque<unsigned int> >::sort()
{
    _container.push_back(2);
};