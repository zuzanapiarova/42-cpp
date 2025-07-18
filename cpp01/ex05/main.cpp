#include "Harl.hpp"

int main(void)
{
    Harl harl;

    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    // testing
    harl.complain("WRONG");
    for (int i = 0; i < 10; i++)
        harl.complain(levels[i%4]);
    harl.complain("SOME");
    harl.complain("WRONG");
    harl.complain("LEVELS");
    return 0;

}