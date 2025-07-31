#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main()
{
    // vector
    int arr1[] = {1, 2, 3, 4, 5};
    std::vector<int> vec(arr1, arr1 + 5);

    // list
    int arr2[] = { 100, 200, 300 };
    const std::list<int> lst(arr2, arr2 + 3);

    // deque
    int arr3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::deque<int> deque(arr3, arr3 + 9);

    try {
        std::vector<int>::iterator it1 = easyfind(vec, 1); // element exists
        std::cout << "Found in vector: " << *it1 << std::endl;

        std::list<int>::const_iterator it2 = easyfind(lst, 300);  // element exists - const container
        std::cout << "Found in list: " << *it2 << std::endl;

        std::deque<int>::iterator it3 = easyfind(deque, 0); // outside of container
        std::cout << "Found in deque: " << *it3 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}