#include "DiamondTrap.hpp"

// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

DiamondTrap::DiamondTrap() : ClapTrap()
{
    std::cout << "DiamondTrap " << this->name << " default constructor called." << std::endl;
    hitPoints = FragTrap::hitPoints;
    energy = ScavTrap::energy;
    damage = FragTrap::damage;
}

// ClapTrap object will use the Name_clap_name name, as defined in subject
// since ScavTrap and FragTrap do not have their own name variabes, they will be using the inherited one from ClapTrap
// the DiamondTrtap will have its own name
DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), name(name)
{
    std::cout << "DiamondTrap " << this->name << " overload constructor called." << std::endl;
    hitPoints = FragTrap::hitPoints;
    energy = ScavTrap::energy;
    damage = FragTrap::damage;
}

DiamondTrap::DiamondTrap(const DiamondTrap& origin) : FragTrap(origin), ScavTrap(origin) // do not have to call ClapTrap(origin) because we use virtual inheritance
{
    std::cout << "DiamondTrap " << name << " copy constructor called." << std::endl;
    this->name = origin.name;
}

DiamondTrap& DiamondTrap::operator = (const DiamondTrap& origin)
{
    std::cout << "Diamond " << name << " copy assignment constructor called." << std::endl;
    if (this != &origin)
    {   
        // do not have to call ClapTrap::operator(origin) because we use virtual inheritance
        ScavTrap::operator=(origin);
        FragTrap::operator=(origin);
    }
    return *this;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << name << " destructor called." << std::endl;
}

// -------------------------------------------- Member functions ---------------------------------------------

// !!! DiamondTrap has two damage members because of multiple inheritance
// !!! So when I call DiamondTrap.attack(), it calls attack function of scavtrap, with scavtrap sub-object
// !!! so it also uses the damage value of this scavtrap object, even though diamondtrap should have damage value of fragtrap
void DiamondTrap::attack(const std::string& target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::takeDamage(unsigned int amount)
{
    std::cout << "DiamondTrap " << this->name << " takes damage of " << amount << " points." << std::endl;
    hitPoints -= amount;
}

void DiamondTrap::beRepaired(unsigned int amount)
{
    if (energy >= 1 && hitPoints > 0)
    {
        std::cout << "DiamondTrap " << this->name << " received " << amount << " hit points." << std::endl;
        hitPoints += amount;
        energy -= 1;
    }
    else
        std::cout << "DiamondTrap " << this->name << " cannot be repaired because of low health or energy." << std::endl;
}

void DiamondTrap::whoAmI()
{
    std::cout << "My name is " << this->name << " and my ClapTrap name is " << ClapTrap::name << "." << std::endl;
}
