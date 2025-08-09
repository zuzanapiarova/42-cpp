#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid input. Expect ./convert <literal>" << std::endl;
        return 1;
    }
    try
    {
        ScalarConverter::convert(argv[1]);
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << "Invalid input: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}