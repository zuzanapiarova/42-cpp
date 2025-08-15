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

    // vector
    int arr3[] = { 1, 2, 2, 2, 2};
    std::vector<int> duplicates(arr3, arr3 + 5);

    // empty
    int arr4[] = {};
    std::deque<int> empty(arr4, arr4);

    // deque
    int arr5[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::deque<int> deque(arr5, arr5 + 9);

    try
    {
        std::vector<int>::iterator it1 = easyfind(vec, 1); // element exists
        std::cout << "Found in vector: " << *it1 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    try
    {
        std::vector<int>::iterator it2 = easyfind(vec, 10); // element does not exist
        std::cout << "Found in vector: " << *it2 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
        std::list<int>::const_iterator it3 = easyfind(lst, 300);  // element exists - const container
        std::cout << "Found in list: " << *it3 << std::endl;
    try
    {
        std::vector<int>::const_iterator it4 = easyfind(duplicates, 2);  // duplicate elements - gets the first occurence
        std::cout << "Found in list: " << *it4 << " on index: " << it4 - duplicates.begin() << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    try
    {
        std::deque<int>::const_iterator it5 = easyfind(empty, 1);  // empty container - element is not found
        std::cout << "Found in list: " << *it5 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    try
    {
        std::deque<int>::iterator it6 = easyfind(deque, 0); // outside of container
        std::cout << "Found in deque: " << *it6 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}