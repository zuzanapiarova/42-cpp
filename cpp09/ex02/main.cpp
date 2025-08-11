#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Wrong arguments. Program expects: ./PmergeMe int1 int2 ... intn";
        return 1;
    }
    try
    {
        PmergeMe p;
        p.populateVector(argc, argv);
        p.populateDeque(argc, argv);

    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}