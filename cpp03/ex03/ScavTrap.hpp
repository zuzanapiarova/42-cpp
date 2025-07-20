#ifndef SCAVTRAP_H
# define SCAVTRAP_H

#include "ClapTrap.hpp"

//        ClapTrap
//         |      
//        |        
//       |          
//      |            
//  ScavTrap

class ScavTrap : virtual public ClapTrap
{
    public:
        ScavTrap();
        ScavTrap(const std::string& name);
        ScavTrap(const ScavTrap& origin);
        ScavTrap& operator = (const ScavTrap& origin);
        virtual ~ScavTrap();

        virtual void attack(const std::string& target);
        virtual void takeDamage(unsigned int amount);
        virtual void beRepaired(unsigned int amount);

        void guardGate();
};

#endif