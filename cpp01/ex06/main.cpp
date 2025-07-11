#include "Harl.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Must specify minimum level of log messages you wish to see.: ./harlFilter { DEBUG, INFO, WARNING, ERROR } " << std::endl;
        return 1;
    }
    
    Harl harl;
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    // testing
    harl.complain(argv[1]);

    return 0;
}