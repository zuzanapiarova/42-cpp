#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Wrong arguments. Program expects: ./PmergeMe int(1) int(2) ... int(n)" << std::endl;
        return 1;
    }
    try
    {
        std::vector<unsigned int>v = populateContainer<std::vector<unsigned int> >(argc, argv);
        // std::deque<unsigned int>d = populateContainer<std::deque<unsigned int> >(argc, argv);
        std::cout << "Max number of calculations (in the worst case): " << calculateMaxNumberOfComparisons(v.size()) << std::endl;

        PmergeMe<std::vector<unsigned int> > V(v);
        // PmergeMe<std::deque<unsigned int> > D(d);

        std::cout << V << std::endl;
        // std::cout << D << std::endl;

        V.sort();
        // D.sort();

        std::cout << V << std::endl;
        // std::cout << D << std::endl;

    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}