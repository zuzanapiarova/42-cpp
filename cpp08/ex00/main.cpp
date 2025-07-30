#include "easyfind.hpp"

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec(arr, arr + 5);

    int arr2[] = {10, 20, 30};
    std::list<int> lst(arr2, arr2 + 3);

    try {
        std::vector<int>::iterator it = easyfind(vec, 3);
        std::cout << "Found in vector: " << *it << std::endl;

        std::list<int>::iterator it2 = easyfind(lst, 25);
        std::cout << "Found in list: " << *it2 << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}