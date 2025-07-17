#include "ScavTrap.hpp"

// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

// !!! I am adding default constructors to see, that if the colon syntax was not done/forgotten when implementing 
// !!! constructors of the children, it will not be silent and it will announce that the default constructor was called !!!
ScavTrap::ScavTrap() : ClapTrap()
{
    std::cout << "ScavTrap " << name << " default constructor called." << std::endl;
    hitPoints = 100;
    energy = 50;
    damage = 20;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)
{
    std::cout << "ScavTrap " << name << " overload constructor called." << std::endl;
    hitPoints = 100;
    energy = 50;
    damage = 20;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << name << " destructor called." << std::endl;
}

// -------------------------------------------- Member functions ---------------------------------------------

void ScavTrap::attack(const std::string& target)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << damage << " points of damage!" << std::endl;
        energy -= 1;
    }
    else
        std::cout << "ScavTrap " << name << " cannot attack " << target << " because of death or low energy." << std::endl;
}

void ScavTrap::takeDamage(unsigned int amount)
{
    std::cout << "ScavTrap " << name << " takes damage of " << amount << " points." << std::endl;
    hitPoints -= amount;
}

void ScavTrap::beRepaired(unsigned int amount)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "ScavTrap " << name << " received " << amount << " hit points." << std::endl;
        hitPoints += amount;
        energy -= 1;
    }
    else
        std::cout << "ScavTrap " << name << " cannot be repaired because of death or low energy." << std::endl;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << name << " has entered Gate Keeper mode." << std::endl;
}