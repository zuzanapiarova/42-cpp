#include "PmergeVector.hpp"

// TODO:
// 1. handle duplicates - now errors if there are any
// 2. prevent receiving negative values and wrapping
// 3. initialize containers with default sizes so it is faster?
// 4. add second container type and optimize for it 
// 5. add measuring time

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Wrong arguments. Program expects: ./PmergeMe int1 int2 ... intn" << std::endl;
        return 1;
    }
    try
    {
        std::vector<int>v = populateContainer(argc, argv);
        // std::cout << "Max number of calculations (in the worst case): " << calculateMaxNumberOfComparisons(v.size()) << std::endl;

        PmergeMe V(v);
        std::cout << V << std::endl;
        V.sort();
        std::cout << V << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}