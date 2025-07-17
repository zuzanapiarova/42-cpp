#ifndef DIAMONDTRAP_H
# define DIAMONDTRAP_H

#include <iostream>
#include <string>

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

/*     ClapTrap
       |      |
      |        |
     |          |
    |            |
 ScavTrap     FragTrap
    |            |
     |          |
      |        |
       |      |
      DiamondTrap
*/

class DiamondTrap : public FragTrap, public ScavTrap
{
    private:
        std::string name;
        
    public:
        DiamondTrap();
        DiamondTrap(const std::string& name);
        ~DiamondTrap();

        virtual void attack(const std::string& target);
        virtual void takeDamage(unsigned int amount);
        virtual void beRepaired(unsigned int amount);

        void whoAmI( void );

};

#endif