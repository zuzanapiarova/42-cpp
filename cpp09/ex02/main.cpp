#include "PmergeMe.hpp"
#include "helpers.cpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Wrong arguments. Program expects: ./PmergeMe int1 int2 ... intn";
        return 1;
    }
    try
    {
        std::vector<unsigned int> v = populateVector(argc, argv);
        std::deque<unsigned int> d = populateDeque(argc, argv);

        PmergeMe<std::vector<unsigned int> > vec(v);
        PmergeMe<std::deque<unsigned int> > deq(d);

        vec.sort();
        deq.sort();

    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}