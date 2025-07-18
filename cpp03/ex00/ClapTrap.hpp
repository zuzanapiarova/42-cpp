#ifndef CLAPTRAP_H
# define CLAPTRAP_H

#include <iostream>
#include <string>

class ClapTrap
{
    private:
        std::string name;
        int         hitPoints;
        int         energy;
        int         damage;

    public:
        ClapTrap();    
        ClapTrap(std::string new_name);
        ClapTrap(ClapTrap& origin);
        ClapTrap& operator = (const ClapTrap& origin);
        ~ClapTrap();

        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);

};

# endif