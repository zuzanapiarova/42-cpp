#include "DiamondTrap.hpp"

// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

// !!! I am adding default constructors to see, that if the colon syntax was not done/forgotten when implementing 
// !!! constructors of the children, it will not be silent and it will announce that the default constructor was called !!!
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
        std::cout << "DiamondTrap " << this->name << " cannot be repaired because of death or low energy." << std::endl;
}

void DiamondTrap::whoAmI()
{
    std::cout << "My name is " << this->name << " and my ClapTrap name is " << ClapTrap::name << "." << std::endl;
}
