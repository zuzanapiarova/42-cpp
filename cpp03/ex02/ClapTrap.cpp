#include "ClapTrap.hpp"

// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

// !!! I am adding default constructors to see, that if the colon syntax was not done/forgotten when implementing 
// !!! constructors of the children, it will not be silent and it will announce that the default constructor was called !!!
ClapTrap::ClapTrap() : name("Anonym"), hitPoints(10), energy(10), damage(0)
{
    std::cout << "Claptrap " << name << " default constructor called." << std::endl;
};    

ClapTrap::ClapTrap(std::string new_name)  : name(new_name), hitPoints(10), energy(10), damage(0)
{
    std::cout << "Claptrap " << name << " overload constructor called." << std::endl;
};

ClapTrap::ClapTrap(ClapTrap& origin)
{
    std::cout << "Claptrap " << name << " copy constructor called." << std::endl;
    this->name = origin.name;
    this->hitPoints = origin.hitPoints;
    this->energy = origin.energy;
    this->damage = origin.damage;
}

ClapTrap& ClapTrap::operator = (const ClapTrap& origin)
{
    std::cout << "Claptrap " << name << " copy assignment constructor called." << std::endl;
    if (this != &origin)
    {    
        this->name = origin.name;
        this->hitPoints = origin.hitPoints;
        this->energy = origin.energy;
        this->damage = origin.damage;
    }
    return *this;
}

ClapTrap::~ClapTrap()
{
    std::cout << "Claptrap " << name << " destructor called." << std::endl;
};

// -------------------------------------------- Member functions ---------------------------------------------

void ClapTrap::attack(const std::string& target)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << damage << " points of damage!" << std::endl;
        energy -= 1;
    }
    else
        std::cout << "ClapTrap " << name << " cannot attack " << target << " because of death or low energy." << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    std::cout << "ClapTrap " << name << " takes damage of " << amount << " points." << std::endl;
    hitPoints -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "ClapTrap " << name << " received " << amount << " hit points." << std::endl;
        hitPoints += amount;
        energy -= 1;
    }
    else
        std::cout << "ClapTrap " << name << " cannot be repaired because of death or low energy." << std::endl;
}