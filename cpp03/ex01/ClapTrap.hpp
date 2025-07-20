#ifndef CLAPTRAP_H
# define CLAPTRAP_H

#include <iostream>
#include <string>

class ClapTrap
{
    protected:
        std::string name;
        int         hitPoints;
        int         energy;
        int         damage;

    public:
        ClapTrap();    
        ClapTrap(const std::string& new_name);
        ClapTrap(const ClapTrap& origin);
        ClapTrap& operator = (const ClapTrap& origin);
        virtual ~ClapTrap();

        virtual void attack(const std::string& target);
        virtual void takeDamage(unsigned int amount);
        virtual void beRepaired(unsigned int amount);

};

# endif