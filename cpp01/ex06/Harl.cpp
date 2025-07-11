#include "Harl.hpp"

// DEBUG level: Debug messages contain contextual information. They are mostly used for problem diagnosis.
void Harl::debug( void )
{
    std::cout << "D: I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger. I really do!" << std::endl;
};

// "INFO" level: These messages contain extensive information. They are helpful for tracing program execution in a production environment.
void Harl::info( void )
{
    std::cout << "I: I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
};

//"WARNING" level: Warning messages indicate a potential issue in the system. However, it can be handled or ignored.
void Harl::warning( void )
{
    std::cout << "W: I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
};

// "ERROR" level: These messages indicate that an unrecoverable error has occurred. This is usually a critical issue that requires manual intervention.
void Harl::error( void )
{
    std::cout << "E: This is unacceptable! I want to speak to the manager now." << std::endl;
};

// using switch with fallthrough - no break for lower levels, because hte upper levels should still be printed anyways
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
            std::cout << "[ DEBUG ]" << std::endl;
            debug();
        case 1:
            std::cout << "[ INFO ]" << std::endl;
            info();
        case 2:
            std::cout << "[ WARNING ]" << std::endl;
            warning();
        case 3:
            std::cout << "[ ERROR ]" << std::endl;
            error();
            break;
        default:
            std::cout << "[ Complaining on another levels. ]" << std::endl;
    }
}