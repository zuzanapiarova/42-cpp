#ifndef FRAGTRAP_H
# define FRAGTRAP_H

#include <iostream>
#include <string>

#include "ClapTrap.hpp"

//        ClapTrap
//             |
//              |
//               |
//                |
//              FragTrap

class FragTrap : virtual public ClapTrap
{
    public:
        FragTrap();
        FragTrap(const std::string& name);
        virtual ~FragTrap();

        virtual void attack(const std::string& target);
        virtual void takeDamage(unsigned int amount);
        virtual void beRepaired(unsigned int amount);

        void highFiveGuys( void );
};

#endif