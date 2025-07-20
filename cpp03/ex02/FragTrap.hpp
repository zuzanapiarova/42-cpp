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

class FragTrap : public ClapTrap
{
    public:
        FragTrap();
        FragTrap(const std::string& name);
        FragTrap(const FragTrap& origin);
        FragTrap& operator = (const FragTrap& origin);
        virtual ~FragTrap();

        virtual void attack(const std::string& target);
        virtual void takeDamage(unsigned int amount);
        virtual void beRepaired(unsigned int amount);

        void highFiveGuys( void );
};

#endif