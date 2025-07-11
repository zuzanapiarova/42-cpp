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

// without function pointers, we would have to add if/else statements and call corresponding functions
// now we store the functions as "variables" and call the needed one from the array wehre they are stored
void Harl::complain(std::string level)
{
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    void (Harl::*functions[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

    for (int i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*functions[i])(); // here function is called from within the class
            return ;
        }
    }
    std::cout << "Harl does not complain on this level." << std::endl;
}