#include <string>
#include <iostream>
#include  "Rpn.hpp"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments. Program expects: ./rpn <expr_in_reverse_polish_notation>" << std::endl;
        return 1;
    }
    try
    {
        // Rpn empty; // test default constructor
        Rpn r(argv[1]);
        std::cout << "Result: " << r.getResult() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}