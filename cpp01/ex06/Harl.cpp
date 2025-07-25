#include "Harl.hpp"

void Harl::debug( void )
{
    std::cout << "[ DEBUG ]" << std::endl << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger. I really do!" << std::endl << std::endl;
};

void Harl::info( void )
{
    std::cout << "[ INFO ]" << std::endl << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl << std::endl;
};

void Harl::warning( void )
{
    std::cout << "[ WARNING ]" << std::endl <<  "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl << std::endl;
};

void Harl::error( void )
{
    std::cout << "[ ERROR ]" << std::endl <<  "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
};

// using switch with fallthrough - no break for lower levels, because the upper levels should still be printed anyways
void Harl::complain(std::string level)
{
    int lvl = -1;
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    for (int i = 0; i < 4; ++i)
        if (levels[i] == level)
            lvl = i;

    switch (lvl)
    {
        case 0:
            debug();
        case 1:
            info();
        case 2:
            warning();
        case 3:
            error();
            break ;
        default:
            std::cout << "[ Complaining on another levels. ]" << std::endl;
    }
}