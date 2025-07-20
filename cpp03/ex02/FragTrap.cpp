#include "FragTrap.hpp"


// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

FragTrap::FragTrap() : ClapTrap()
{
    std::cout << "FragTrap " << name << " default constructor called." << std::endl;
    hitPoints = 100;
    energy = 100;
    damage = 30;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
    std::cout << "FragTrap " << name << " overload constructor called." << std::endl;
    hitPoints = 100;
    energy = 100;
    damage = 30;
}

FragTrap::FragTrap(const FragTrap& origin) : ClapTrap(origin)
{
    std::cout << "FragTrap " << name << " copy constructor called." << std::endl;
}

FragTrap& FragTrap::operator = (const FragTrap& origin)
{
    std::cout << "FragTrap " << name << " copy assignment constructor called." << std::endl;
    if (this != &origin)
        ClapTrap::operator=(origin); // delegate to base class
    return *this;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << name << " destructor called." << std::endl;
}

// -------------------------------------------- Member functions ---------------------------------------------

// !!! I am adding default constructors to see, that if the colon syntax was not done/forgotten when implementing 
// !!! constructors of the children, it will not be silent and it will announce that the default constructor was called !!!
void FragTrap::attack(const std::string& target)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "FragTrap " << name << " attacks " << target << ", causing " << damage << " points of damage!" << std::endl;
        energy -= 1;
    }
    else
        std::cout << "FragTrap " << name << " cannot attack " << target << " because of death or low energy." << std::endl;
}

void FragTrap::takeDamage(unsigned int amount)
{
    std::cout << "FragTrap " << name << " takes damage of " << amount << " points." << std::endl;
    hitPoints -= amount;
}

void FragTrap::beRepaired(unsigned int amount)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "FragTrap " << name << " received " << amount << " hit points." << std::endl;
        hitPoints += amount;
        energy -= 1;
    }
    else
        std::cout << "FragTrap " << name << " cannot be repaired because of death or low energy." << std::endl;
}

void FragTrap::highFiveGuys()
{
    std::cout << "FragTrap " << name << " wants to high five." << std::endl;
}