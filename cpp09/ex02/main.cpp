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
        std::vector<unsigned int> v = populateVector(argc, argv);
        std::deque<unsigned int> d = populateDeque(argc, argv);

        PmergeMe<std::vector<unsigned int> > vec(v);
        PmergeMe<std::deque<unsigned int> > deq(d);

        printContainer(vec.getContainer());
        printContainer(deq.getContainer());

        vec.sort();
        deq.sort();

        printContainer(vec.getContainer());
        printContainer(deq.getContainer());

    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}