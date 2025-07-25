#include "Harl.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Must input a single level of log messages you wish to see.: ./harlFilter { DEBUG, INFO, WARNING, ERROR } " << std::endl;
        return 1;
    }

    Harl harl;
    harl.complain(argv[1]);

    return 0;
}